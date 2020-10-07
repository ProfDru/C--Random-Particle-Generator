#include <system\controls.h>

#include <GLFW\glfw3.h>

#include <numeric>
#include <utils.h>
#include <sys_time.h>

namespace rpg {

/*! \brief Maps GLFW keys to control statments */
enum class CONTROL_MAP {
  FORWARD = GLFW_KEY_W,
  BACKWARD = GLFW_KEY_S,
  RIGHT = GLFW_KEY_D,
  LEFT = GLFW_KEY_A,

  BOOST = GLFW_KEY_LEFT_SHIFT,
  BRAKE = GLFW_KEY_LEFT_CONTROL,

  PAUSE = GLFW_KEY_TAB
};

static double last_time = 0;

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

inline bool DidPress(GLFWwindow* window, CONTROL_MAP key) {
  return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
}

inline glm::vec2 CalcMovement(GLFWwindow* window) {
  glm::vec2 control(0, 0);

  if (DidPress(window, CONTROL_MAP::FORWARD))
    control.y += 1;
  if (DidPress(window, CONTROL_MAP::BACKWARD))
    control.y -= 1;
  if (DidPress(window, CONTROL_MAP::RIGHT))
    control.x += 1;
  if (DidPress(window, CONTROL_MAP::LEFT))
    control.x -= 1;

  return control;
}

inline float CalcBoostMultiplier(GLFWwindow* window) {
  const float boost_factor = 2.5;
  float boost_multiplier = 1.0f;

  if (DidPress(window, CONTROL_MAP::BOOST))
    boost_multiplier *= boost_factor;
  if (DidPress(window, CONTROL_MAP::BRAKE))
    boost_multiplier /= boost_factor;

  return boost_multiplier;
}

/*! \brief Calculate the difference between the cursor's position and the center
 * of the screen in pixels */
inline glm::vec2 CalcDirection(GLFWwindow* window) {
  auto win_center = ScreenCenter();

  double cursor_x, cursor_y;
  glfwGetCursorPos(window, &cursor_x, &cursor_y);
  glfwSetCursorPos(window, win_center.x, win_center.y);

  return glm::vec2(win_center.x - cursor_x, win_center.y - cursor_y);
}

MoveInfo Move(GLFWwindow* window) {
  const float speed = 2.5f;
  const float mouse_sensitivity = 0.15f;
  const float change_in_time = CalculateChangeInTime();
  const float boost_multi = CalcBoostMultiplier(window);

  if (last_time == 0) {
    last_time = change_in_time;
    return MoveInfo();
  }

  glm::vec2 movement_change =
      CalcMovement(window) * speed * change_in_time * boost_multi;
  glm::vec2 direction_change =
      CalcDirection(window) * mouse_sensitivity * change_in_time;

  return (MoveInfo{movement_change, direction_change});
}

static bool pause_pressed_last_frame = false;

bool ShouldPause(GLFWwindow* win, bool paused_state) {
  bool pause_pressed = DidPress(win, CONTROL_MAP::PAUSE);

  // If pause is pressed it'll be considered as pressed for every frame the key
  // is held. To handle this we'll need to keep track of last time it was
  // pushed.
  if (pause_pressed_last_frame && pause_pressed)
    return paused_state;
  else
    pause_pressed_last_frame = false;

  if (DidPress(win, CONTROL_MAP::PAUSE)) {
    // If we aren't paused, pause and show cursor.
    // If we are paused Unpause and hide the cursor
    auto cursor_mode = paused_state ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;

    glfwSetInputMode(win, GLFW_CURSOR, cursor_mode);
    pause_pressed_last_frame = true;
    return !paused_state;
  } else {
    return paused_state;
  }
}

}  // namespace rpg