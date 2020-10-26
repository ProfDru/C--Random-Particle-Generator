#pragma once

#include <vector>
#include <string>
#include <memory>

#include <window/hud/widget.h>

namespace rpg::hud {
class Window {
  std::string name;
  float x, y;
  bool is_hud;  //< Determines whether or not this window should draw while
                // paused

 private:
  std::vector<std::unique_ptr<Widget>> widgets;

 public:
  Window(const std::string& name,
         bool is_hud = false,
         float x_pos = 0,
         float y_pos = 0);

  void Draw(bool paused = false);

  void AddWidget(Widget* widget);
};
}  // namespace rpg::hud