#include <scene.h>
#include <rendering\renderer.h>
#include <rendering\preloaded_shaders.h>
#include <entities/entity.h>
#include <entities/entity_registry.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <controls.h>

#include <cassert>
#include <exception>
#include <iostream>
#include <utils.h>

namespace rpg {

/*! \brief Called by glfw when there's an issue */
void ErrorCallBack(int, const char* err_str) {
  std::cerr << "] GLFW Error: " << err_str << std::endl;
}

/*! \brief Called by OpenGL when there's an error. */
void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const char* message,
                                const void* userParam) {
  // return;
  if (severity != 0x826b)
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
}

/*!
    \brief Initializes glew and prints an errof if one is found
    \returns false if GLEW couldn't be initialized, true if it could
*/
bool InitGlew() {
  auto glewinit_res = glewInit();
  if (glewinit_res != GLEW_OK) {
    fprintf(stderr, "Glew init error: %s\n", glewGetErrorString(glewinit_res));
    return false;
  }
  return true;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

/*! \brief Initalize and return the glfw window*/
GLFWwindow* InitWindow() {
  printf("Initializing GLFW...\n");
  glewExperimental = true;

  // throw some exception if this cannot init (Should be an actual exception)
  if (!glfwInit())
    throw std::exception();

  // Create a new window, throw if it fails
  printf("Creating Window...\n");
  GLFWwindow* window = glfwCreateWindow(window_width, window_height,
                                        "Random Particle Engine", NULL, NULL);
  assert(window != NULL);

  // Set the new window as the current context
  glfwMakeContextCurrent(window);

  // Enable depth buffer test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glDepthRange(0.0f, 1.0f);

  // Enable several opengl settings
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_POINT_SPRITE);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  // Make the window resizable and update at 60 FPS
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_REFRESH_RATE, 120);
  glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glEnable(GL_PROGRAM_POINT_SIZE);

  printf("Initializing GLEW...\n");
  bool did_init = InitGlew();
  assert(did_init);

  printf("Returning Window...\n");
  return window;
}

void Scene::Start() {
  // Setup the error callback for GLFW
  glfwSetErrorCallback(ErrorCallBack);

  // Create a window to set as our window
  this->current_window = InitWindow();

  // Setup error callback for OpenGL
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  glfwSetWindowSizeCallback(this->current_window, WindowResizeCallback);
  glfwSetFramebufferSizeCallback(this->current_window, FramebufferSizeCallback);

  // Create a particle engine to draw
  printf("Creating Particle Engine and Camera...");
  this->PI.emplace(ParticleEngine());
  this->main_camera = Camera(0, 0, 2, 0, 0, -1);

  glfwSetInputMode(this->current_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set Point Size
  // glPointSize(10.0f);

  this->PI->SetID(Registry::GetNextID());

  // initiate draw loop
  printf("Beginning Draw Loop. \n");
  this->DrawLoop();
}

inline bool HandleMovement(Camera& camera, GLFWwindow* window) {
  auto movement = Move(window);

  if (!movement.empty()) {
    camera.Move(movement.position_change, movement.direction_change);
    glm::mat4 MVP = camera.CalculateMVP();
    rendering::Renderer::UpdateMVP(MVP);
    return true;
  } else
    return false;
}

void Scene::DrawLoop() {
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(this->current_window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set the backgorun color
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  rendering::Renderer::AssignShader(*(this->PI), rendering::RainbowShader);
  do {
    PI->Update();
    HandleMovement(this->main_camera, this->current_window);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rendering::Renderer::Render(*(this->PI));

    glfwSwapBuffers(current_window);
    this->paused = ShouldPause(this->current_window, this->paused);
    glfwPollEvents();

  }  // End the loop if the escape key was pressed or the window was closed
  while (glfwGetKey(current_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(current_window) == 0);
}

}  // namespace rpg