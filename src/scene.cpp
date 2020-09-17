#include <GL/glew.h>
#include <scene.h>

#include <cassert>
#include <exception>
#include <iostream>


namespace rpg {

/*! \brief Called by glfw when there's an issue */
void ErrorCallBack(int, const char *err_str) {
  std::cerr << "] GLFW Error: " << err_str << std::endl;
}

/*! \brief Initalize and return the glfw window*/
GLFWwindow *InitWindow() {
  glewExperimental = true;

  if (!glfwInit())
    throw std::exception();

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "Random Particle Engine", NULL, NULL);
  assert(window != NULL);

  glfwMakeContextCurrent(window);
  return window;
}

void Scene::Start() {
  glfwSetErrorCallback(ErrorCallBack);
  this->current_window = InitWindow();
  this->DrawLoop();
}

void Scene::DrawLoop() {
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(this->current_window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  do {
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause
    // flickering, so it's there nonetheless.
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw nothing, see you in tutorial 2 !
    // Swap buffers
    glfwSwapBuffers(current_window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(current_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(current_window) == 0);
}

Scene::~Scene() { glfwTerminate(); }

} // namespace rpg