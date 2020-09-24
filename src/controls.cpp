#include <controls.h>
#include <numeric>
#include <utils.h>

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
  Resolution win_res = GetWindowResolution(window);
  Resolution win_center = win_res.GetCenterPoint();

  double cursor_x, cursor_y;
  glfwGetCursorPos(window, &cursor_x, &cursor_y);
  glfwSetCursorPos(window, win_center.width, win_center.height);

  return glm::vec2(win_center.width - cursor_x, win_center.height - cursor_y);
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