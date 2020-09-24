#include <controls.h>
#include <numeric>

namespace rpg {
static double last_time = 0;

float CalculateChangeInTime() {
  double current_time = glfwGetTime();
  return float(current_time - last_time);
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

/*! \brief Calculate the difference between the cursor's position and the center
 * of the screen in pixels */
inline glm::vec2 CalcDirection(GLFWwindow* window) {
  int window_width, window_height;
  glfwGetWindowSize(window, &window_width, &window_height);

  const float center_x = window_width / 2;
  const float center_y = window_height / 2;

  double cursor_x, cursor_y;
  glfwGetCursorPos(window, &cursor_x, &cursor_y);
  glfwSetCursorPos(window, center_x, center_y);

  return glm::vec2(center_x - cursor_x, center_y - cursor_y);
}

MoveInfo Move(GLFWwindow* window) {
  const float speed = 0.5f;
  const float mouse_sensitivity = 0.05f;
  const float change_in_time = CalculateChangeInTime();

  if (last_time == 0) {
    last_time = change_in_time;
    return MoveInfo();
  }

  glm::vec2 movement_change = CalcMovement(window) * speed * change_in_time;
  glm::vec2 direction_change =
      CalcDirection(window) * mouse_sensitivity * change_in_time;

  last_time = glfwGetTime();
  return (MoveInfo{movement_change, direction_change});
}

}  // namespace rpg