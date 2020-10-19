#pragma once

#include <vector>
#include <string>
#include <memory>

#include <window/hud/widget.h>

namespace rpg::hud {
class Window {
  std::string name;
  float x, y;

 private:
  std::vector<std::unique_ptr<Widget>> widgets;

 public:
  Window(const std::string& name, float x_pos = 0, float y_pos = 0);

  void Draw();

  void AddWidget(Widget* widget);
};
}  // namespace rpg::hud