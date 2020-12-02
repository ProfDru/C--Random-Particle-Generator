#pragma once
#include <vector>

#include <glm/glm.hpp>

class GLFWwindow;

namespace rpg {

/*! \brief Holds vectors containing a change in position and direction */
struct MoveInfo {
  glm::vec2 position_change;
  glm::vec2 direction_change;

  inline MoveInfo() : position_change(0, 0), direction_change(0, 0){};

  inline MoveInfo(glm::vec2 pos_change, glm::vec2 dir_change)
      : position_change(pos_change), direction_change(dir_change){};

  inline bool empty() {
    return (this->position_change.length() <= 0 &&
            this->direction_change.length() <= 0);
  }
};

/*! \brief Determine the change in the camera's position and rotation based on
 * inputs. */
MoveInfo Move(float base_speed = 2.5f, float boost_multiplier = 2.5f);

}  // namespace rpg