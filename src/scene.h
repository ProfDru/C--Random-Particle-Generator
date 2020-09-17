#include <GLFW/glfw3.h>

namespace rpg {

/*! \brief Manages the state of the OpenGL renderer */
class Scene {

private:
  GLFWwindow *current_window;

  /*! \brief Draw in a loop and pass info to the camera */
  void DrawLoop();

public:
  /*!
      \brief Start rendering the scene with the current options
      \details This will initiate the draw loop here
  */
  void Start();

  ~Scene();
};
} // namespace rpg