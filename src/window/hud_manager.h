#pragma once

#include <string>
#include <AntTweakBar.h>

namespace rpg {
class HudManager {
 private:
  inline static TwBar* main_bar = NULL;
  inline static std::string name = "main";

  /*! \brief Change the value of a parameter for this bar */
  static void SetParam(const std::string& param, const std::string& val);

 public:
  /*! \brief Initialize the hud and create the bar */
  static void Init(float window_x, float window_y);

  /*! \brief Draw the to the screen */
  static void Draw();

  /*! \brief Create a slider for the given floating point number*/
  static void AddSlider(float* num,
                        std::string name,
                        float min = 0,
                        float max = 1,
                        float step = 0.01,
                        std::string label = "",
                        std::string group = "Default");

  static bool KeyCallBack(int key, int mods);
  static bool MouseClickCallback(int mouse_action, int mouse_button);
  static bool MousePosCallback(int mouseX, int mouseY);
  static bool ScrollWheelCallback(int pos);
  static bool WindowResizecallback(int width, int height);
};
}  // namespace rpg