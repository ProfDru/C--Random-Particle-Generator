#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace rpg {

/*! \brief Holds vectors containing a change in position and direction */
struct MoveInfo {
  glm::vec2 position_change;
  glm::vec2 direction_change;

  inline MoveInfo() : position_change(0, 0), direction_change(0, 0){};

  inline MoveInfo(glm::vec2 pos_change, glm::vec2 dir_change)
      : position_change(pos_change), direction_change(dir_change){};
};

/*! \brief Maps GLFW keys to control statments */
enum class CONTROL_MAP {
  FORWARD = GLFW_KEY_W,
  BACKWARD = GLFW_KEY_S,
  RIGHT = GLFW_KEY_D,
  LEFT = GLFW_KEY_A,

  BOOST = GLFW_KEY_LEFT_SHIFT,
  BRAKE = GLFW_KEY_LEFT_CONTROL
};

/*! \brief Determine the change in the camera's position and rotation based on
 * inputs. */
MoveInfo Move(GLFWwindow* window);
}  // namespace rpg