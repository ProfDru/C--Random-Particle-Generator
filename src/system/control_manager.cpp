#include <system/control_manager.h>
#include <system/bindings.h>

#include <iostream>

namespace rpg::input {
std::vector<KEY_STATE> InputManager::action_states =
    std::vector<KEY_STATE>(512, KEY_STATE::MINUS);

Bindings InputManager::current_bindings = Bindings();

KEY_STATE InputManager::GetKeyState(ACTION action) {
  const int index = static_cast<int>(action);

  return action_states[index];
}

void InputManager::SetState(ACTION act, KEY_STATE new_state) {
  const int index = static_cast<int>(act);

  action_states[index] = new_state;
}

void InputManager::SetBindings(const Bindings& binds) {
  current_bindings = binds;
}

void InputManager::RecordChangeInKeyState(bool is_down, int key_code) {
  ACTION action = current_bindings.GetAction(key_code);

  if (action != ACTION::NONE) {
    KEY_STATE new_state = is_down ? KEY_STATE::PLUS : KEY_STATE::MINUS;
    SetState(action, new_state);
  }
}

bool InputManager::IsActive(ACTION action) {
  const auto key_state = GetKeyState(action);
  return key_state == KEY_STATE::PLUS;
}

float InputManager::GetCursorX() {
  return InputManager::cursor_x;
}

float InputManager::GetCursorY() {
  return InputManager::cursor_y;
}

void InputManager::TrackMouse(bool is_focused) {
  input::InputManager::is_capturing_mouse = is_focused;
}

void InputManager::UpdateCursorXY(float x, float y) {
  if (is_capturing_mouse) {
    cursor_x = x;
    cursor_y = y;
  }
}

void InputManager::Pause() {
  is_paused = !is_paused;
}

bool InputManager::IsPaused() {
  return is_paused;
}
bool InputManager::IsTrackingMouse() {
  return is_capturing_mouse;
}

}  // namespace rpg::input