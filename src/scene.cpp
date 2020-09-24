#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <scene.h>
#include <controls.h>

#include <cassert>
#include <exception>
#include <iostream>

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
                                const GLchar* message,
                                const void* userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
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

/*! \brief Initalize and return the glfw window*/
GLFWwindow* InitWindow() {
  printf("Initializing GLFW...\n");
  glewExperimental = true;

  // throw some exception if this cannot init (Should be an actual exception)
  if (!glfwInit())
    throw std::exception();

  // Enable depth buffer test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // Enable several opengl settings
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_POINT_SPRITE);
  glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

  // Make the window resizable and update at 60 FPS
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_REFRESH_RATE, 60);

  // Create a new window, throw if it fails
  printf("Creating Window...\n");
  GLFWwindow* window =
      glfwCreateWindow(1280, 720, "Random Particle Engine", NULL, NULL);
  assert(window != NULL);

  // Set the new window as the current context
  glfwMakeContextCurrent(window);

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

  // Create a particle engine to draw
  printf("Creating Particle Engine and Camera...");
  this->PI.emplace(ParticleEngine());
  this->main_camera = Camera(0, 0, 2, 0, 0, -1);

  // Set Point Size
  glPointSize(10.0f);

  // initiate draw loop
  printf("Beginning Draw Loop. \n");
  this->DrawLoop();
}

void Scene::DrawLoop() {
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(this->current_window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set the backgorun color
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  do {
    // Poll keyboard events
    glfwPollEvents();
    auto moves = Move(this->current_window);
    this->main_camera.Move(moves.position_change, moves.direction_change);

    auto MVP = this->main_camera.CalculateMVP();
    this->PI->SetCameraPosition(MVP);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the particle engine
    this->PI->Draw();

    glfwSwapBuffers(current_window);

  }  // End the loop if the escape key was pressed or the window was closed
  while (glfwGetKey(current_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(current_window) == 0);
}

Scene::~Scene() {
  glfwTerminate();
}

}  // namespace rpg