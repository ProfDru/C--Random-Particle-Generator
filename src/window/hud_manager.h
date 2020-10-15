#pragma once

#include <string>
#include <AntTweakBar.h>

namespace rpg {
class HudManager {
 private:
  inline static TwBar* main_bar = NULL;
  inline static std::string name = "main";

 public:
  /*! \brief Initialize the hud and create the bar */
  static void Init();

  /*! \brief Create a new variable adn add it to the hud */
  static void CreateVar();

  static bool KeyCallBack(int key, int mods);
  static bool MouseClickCallback(int mouse_action, int mouse_button);
  static bool MousePosCallback(int mouseX, int mouseY);
  static bool ScrollWheelCallback(int pos);
  static bool WindowResizecallback(int width, int height);
};
}  // namespace rpg