#include <system/control_manager.h>
#include <system/bindings.h>

#include <iostream>

namespace rpg::input {
std::vector<KEY_STATE> InputManager::action_states =
    std::vector<KEY_STATE>(128, KEY_STATE::MINUS);

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

  if (action != ACTION::NONE && action != ACTION::SIZE) {
    KEY_STATE new_state = is_down ? KEY_STATE::PLUS : KEY_STATE::MINUS;
    SetState(action, new_state);
  }
}

bool InputManager::IsActive(ACTION action) {
  return GetKeyState(action) == KEY_STATE::PLUS;
}

double InputManager::GetCursorX() {
  return InputManager::cursor_x;
}

double InputManager::GetCursorY() {
  return InputManager::cursor_y;
}

void InputManager::UpdateCursorXY(double x, double y) {
  cursor_x = x;
  cursor_y = y;
}
}  // namespace rpg::input