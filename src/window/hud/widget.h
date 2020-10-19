#pragma once

#include <string>

namespace rpg::hud {

class Widget {
 public:
  std::string name;
  std::string tooltip;

  virtual void Draw() = 0;

  virtual ~Widget(){};
};
}  // namespace rpg::hud