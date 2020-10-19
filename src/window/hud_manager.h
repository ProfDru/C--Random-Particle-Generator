#pragma once

#include <string>

class GLFWwindow;

namespace rpg {
class HudManager {
 private:
  /*! \brief Change the value of a parameter for this bar */
  static void SetParam(const std::string& param, const std::string& val);

 public:
  /*! \brief Initialize the hud and create the bar */
  static void Init(GLFWwindow* win);

  /*! \brief Draw the to the screen */
  static void Draw();

  // These are unused for now, but may be useful in the future since I probably
  // want to block click events at times
  static bool KeyCallBack(int key, int mods);
  static bool MouseClickCallback(int mouse_action, int mouse_button);
  static bool MousePosCallback(int mouseX, int mouseY);
  static bool ScrollWheelCallback(int pos);
  static bool WindowResizecallback(int width, int height);
};
}  // namespace rpg