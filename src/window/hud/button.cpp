#include <window\hud\button.h>

#include <imgui.h>

namespace rpg::hud {
Button::Button(const std::string& name,
               const std::string& label,
               std::function<void()> press_function,
               Button::MODE mode)
    : Label(name, label), press_function(press_function), mode(mode) {}

bool evaluate_bool(bool is_pressed,
                   bool was_pressed_last_frame,
                   Button::MODE mode) {
  switch (mode) {
    case Button::MODE::CONSTANT:
      return is_pressed;
      break;
    case Button::MODE::ONE_FRAME:
      return (is_pressed && !was_pressed_last_frame);
      break;
    default:
      return false;
      break;
  }
}

void Button::Draw() {
  const bool is_pressed = ImGui::Button(this->text.c_str());
  const bool should_be_pressed =
      evaluate_bool(is_pressed, this->was_pressed_last_frame, this->mode);

  if (should_be_pressed)
    this->press_function();

  this->was_pressed_last_frame = is_pressed;
}
}  // namespace rpg::hud