#pragma once
#include <entities\particle_system.h>
#include <camera.h>
#include <window\window.h>

#include <stdlib.h>
#include <stdio.h>
#include <optional>

class GLFWwindow;

namespace rpg {

/*! \brief Manages the state of the OpenGL renderer */
class Scene {
  std::optional<ParticleEngine> PI;
  Camera main_camera;
  bool paused = false;

 private:
  Window current_window;
  /*! \brief Draw in a loop and pass info to the camera */
  void DrawLoop();

 public:
  /*!
      \brief Start rendering the scene with the current options
      \details This will initiate the draw loop here
  */
  void Start();
};
}  // namespace rpg