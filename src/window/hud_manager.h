#pragma once

#include <window/hud/hud_window.h>
#include <window/hud/widget.h>

#include <string>
#include <vector>
#include <unordered_map>

class GLFWwindow;

namespace rpg {
class HudManager {
 private:
  //< Contains all windows and their names for access
  static std::unordered_map<std::string, hud::Window> windows;

 public:
  /*! \brief Initialize the hud and create the bar */
  static void Init(GLFWwindow* win);

  /*! \brief Draw the to the screen */
  static void Draw();

  /*! \brief Create a new window with the specified name */
  static void CreateWindow(const std::string& name);

  /*! \brief Add a widget to an existing window.

      \note This will assign ownership of the widget to the window.
  */
  static void AddWidget(const std::string& window_name, hud::Widget* widget);

  // These are unused for now, but may be useful in the future since I probably
  // want to block click events at times
  static bool KeyCallBack(int key, int mods);
  static bool MouseClickCallback(int mouse_action, int mouse_button);
  static bool MousePosCallback(int mouseX, int mouseY);
  static bool ScrollWheelCallback(int pos);
  static bool WindowResizecallback(int width, int height);
};
}  // namespace rpg