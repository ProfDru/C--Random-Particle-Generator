#pragma once
#include <particle_system.h>
#include <camera.h>

#include <stdlib.h>
#include <stdio.h>
#include <GLFW\glfw3.h>
#include <optional>

namespace rpg {

/*! \brief Manages the state of the OpenGL renderer */
class Scene {
  std::optional<ParticleEngine> PI;
  Camera main_camera;

 private:
  GLFWwindow* current_window;

  /*! \brief Draw in a loop and pass info to the camera */
  void DrawLoop();

  /*! \brief Called every time the window is resized */
  void WindowResizeCallback(GLFWwindow* window, int width, int height);

 public:
  /*!
      \brief Start rendering the scene with the current options
      \details This will initiate the draw loop here
  */
  void Start();

  ~Scene();
};
}  // namespace rpg