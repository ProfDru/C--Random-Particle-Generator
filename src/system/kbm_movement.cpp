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

inline float CalcBoostMultiplier(float speed, float boost_multi) {
  if (DidPress(ACTION::BOOST))
    speed *= boost_multi;

  if (DidPress(ACTION::BRAKE))
    speed /= boost_multi;

  return speed;
}

inline float magnitude(const glm::vec2& vector) {
  return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

/*! \brief Calculate the difference between the cursor's position and the center
 * of the screen in pixels */
inline glm::vec2 CalcDirection() {
  const auto win_center = Globals::ScreenCenter();

  const float cursor_x = InputManager::GetCursorX();
  const float cursor_y = InputManager::GetCursorY();

  glm::vec2 change_in_cursor(floor(win_center.x - cursor_x),
                             floor(win_center.y - cursor_y));
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

inline bool check_for_restart() {
  return DidPress(rpg::input::ACTION::RESET);
}

MoveInfo Move(float speed, float boost_multi) {
  if (check_for_restart())
    return MoveInfo(true);

  const float mouse_sensitivity = 0.15f;
  const float change_in_time = CalculateChangeInTime();
  speed = CalcBoostMultiplier(speed, boost_multi);

  if (last_time == 0) {
    last_time = change_in_time;
    return MoveInfo();
  }

  PauseLogic();
  if (!InputManager::IsTrackingMouse())
    return MoveInfo();
  else {
    glm::vec2 movement_change = CalcMovement() * speed * change_in_time;
    glm::vec2 direction_change =
        CalcDirection() * mouse_sensitivity * change_in_time;
    return (MoveInfo{movement_change, direction_change});
  }
}

}  // namespace rpg