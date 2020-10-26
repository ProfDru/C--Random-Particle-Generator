#pragma once

#include <window/hud/hud_window.h>
#include <window/hud/widget.h>

#include <string>
#include <vector>
#include <unordered_map>

class GLFWwindow;

namespace rpg {

/*! \brief Contains and manages state for all functionality relevant to drawing
  the Heads Up Display/GUI
 */
class HudManager {
 private:
  inline static bool enable = true;  //< Whether or not to draw GUI windows

  //< Contains all windows and their names for later access
  static std::unordered_map<std::string, hud::Window> windows;

 public:
  /*! \brief Initialize the HUD Context.

    \warning The GUI will not function unless this function is called with the
    active GLFW display before attempting to draw it
  */
  static void Init(GLFWwindow* win);

  /*! \brief Draw the GUI/HUD. */
  static void Draw();

  /*! \brief Create and begin drawing a new window. */
  static void CreateWindow(const std::string& name,
                           float x_pos = 0,
                           float y_pos = 0,
                           bool is_hud = false);

  /*! \brief Add a widget to an existing window.

      \note This will assign ownership of the widget to the window.

      \see hud::Window::AddWidget
  */
  static void AddWidget(const std::string& window_name, hud::Widget* widget);

  /*! \brief Hide or show the UI */
  static void SetEnabled(bool is_enabled);

  // These are unused for now, but may be useful in the future since I probably
  // want to block click events at times
  static bool KeyCallBack(int key, int mods);
  static bool MouseClickCallback(int mouse_action, int mouse_button);
  static bool MousePosCallback(int mouseX, int mouseY);
  static bool ScrollWheelCallback(int pos);
  static bool WindowResizecallback(int width, int height);
};
}  // namespace rpg