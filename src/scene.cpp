#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <scene.h>

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
  glewExperimental = true;

  // throw some exception if this cannot init (Should be an actual exception)
  if (!glfwInit())
    throw std::exception();

  // Make the window resizable
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a new window, throw if it fails
  GLFWwindow* window =
      glfwCreateWindow(1280, 720, "Random Particle Engine", NULL, NULL);
  assert(window != NULL);

  // Set the new window as the current context
  glfwMakeContextCurrent(window);

  assert(InitGlew());
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
  this->PI = ParticleEngine();

  // initiate draw loop
  this->DrawLoop();
}


void Scene::DrawLoop() {
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(this->current_window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set the backgorun color
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  do {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the particle engine
    this->PI->Draw();

    // Swap buffers (update the screen)
    glfwSwapBuffers(current_window);
    
    // Poll keyboard events
    glfwPollEvents();

  }  // End the loop if the escape key was pressed or the window was closed
  while (glfwGetKey(current_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(current_window) == 0);
}

Scene::~Scene() {
  glfwTerminate();
}

}  // namespace rpg