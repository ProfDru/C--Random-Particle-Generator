#include <system\kbm_movement.h>

#include <system\control_enums.h>
#include <system\control_manager.h>
#include <sys_time.h>
#include <utils.h>

#include <numeric>
#include <iostream>

using rpg::input::ACTION;
using rpg::input::InputManager;
namespace rpg {

static double last_time = 0;
static bool pause_pressed_last_frame = false;

float CalculateChangeInTime() {
  double current_time = system::get_precise_time_ms() / 1000.0;

  if (last_time == 0) {
    last_time = current_time;
    return 0;
  } else {
    auto return_value = float(current_time - last_time);
    last_time = current_time;
    return return_value;
  }
}

bool DidPress(ACTION act) {
  return InputManager::IsActive(act);
}

inline glm::vec2 CalcMovement() {
  glm::vec2 control(0, 0);

  if (DidPress(ACTION::FORWARD))
    control.y += 1;
  if (DidPress(ACTION::BACKWARD))
    control.y -= 1;
  if (DidPress(ACTION::RIGHT))
    control.x += 1;
  if (DidPress(ACTION::LEFT))
    control.x -= 1;

  return control;
}

inline float CalcBoostMultiplier() {
  const float boost_factor = 2.5;
  float boost_multiplier = 1.0f;

  if (DidPress(ACTION::BOOST))
    boost_multiplier *= boost_factor;
  if (DidPress(ACTION::BRAKE))
    boost_multiplier /= boost_factor;

  return boost_multiplier;
}

/*! \brief Calculate the difference between the cursor's position and the center
 * of the screen in pixels */
inline glm::vec2 CalcDirection() {
  const auto win_center = Globals::ScreenCenter();

  const float cursor_x = InputManager::GetCursorX();
  const float cursor_y = InputManager::GetCursorY();

  glm::vec2 change_in_cursor(win_center.x - cursor_x, win_center.y - cursor_y);

  return change_in_cursor;
}

inline bool PauseLogic() {
  const bool pause_pressed = DidPress(rpg::input::ACTION::PAUSE);
  if (!pause_pressed)
    pause_pressed_last_frame = false;
  else if (pause_pressed && !pause_pressed_last_frame) {
    pause_pressed_last_frame = true;
    InputManager::Pause();
  }
  return true;
}

MoveInfo Move() {
  const float speed = 2.5f;
  const float mouse_sensitivity = 0.15f;
  const float change_in_time = CalculateChangeInTime();
  const float boost_multi = CalcBoostMultiplier();

  if (last_time == 0) {
    last_time = change_in_time;
    return MoveInfo();
  }

  PauseLogic();
  if (!InputManager::IsTrackingMouse())
    return MoveInfo();
  else {
    glm::vec2 movement_change =
        CalcMovement() * speed * change_in_time * boost_multi;
    glm::vec2 direction_change =
        CalcDirection() * mouse_sensitivity * change_in_time;
    return (MoveInfo{movement_change, direction_change});
  }
}

}  // namespace rpg