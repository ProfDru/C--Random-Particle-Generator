#include <functional>
#include <array>

class GLFWwindow;

namespace rpg {
class Window {
 public:
  std::function<void(double, double)> mouse_callback;
  std::function<void(bool, int)> key_callback;
  std::function<void(float, float)> window_resize_callback;

  float width, height;

  std::array<float, 3> clear_color = {0.1, 0.1, 0.1};
  GLFWwindow* win;

  /*! \brief Initialize the window and OpenGL Context */
  void Init(float width = 1280, float height = 720);

  /*! \brief Set the callback function for when inputs are updated*/
  void SetKeyCallback(std::function<void(bool, int)> func);

  /*! \brief Set the callback function for when inputs are updated*/
  void SetResizeCallback(std::function<void(float, float)> func);

  /*! \brief Set the callback for when the mouse is moved */
  void SetMouseCallback(std::function<void(float, float)> func);

  /*! \brief Forcibly call the resize callback */
  void UpdateSize();

  /*! \brief Clear the current screen */
  void Clear();
  /*! \brief Update the current display.

          \returns `true` if this should keep rendering
          \returns `false` if the user intends to quit

  */
  bool Redraw();
};

}  // namespace rpg