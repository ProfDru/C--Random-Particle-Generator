#pragma once

#include <window/hud/widget.h>
#include <window/hud/label.h>

#include <string>
namespace rpg::hud {
class FPSCounter : public Label {
 public:
  std::string text;

  FPSCounter(const std::string& name);

  virtual void Draw() override;

  void UpdateText(std::string& new_text);

  ~FPSCounter(){};
};
}  // namespace rpg::hud