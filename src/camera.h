#include <glm/glm.hpp>

namespace rpg {

class Camera {
 public:
  glm::vec3 pos;
  glm::vec3 rot;
  glm::vec3 up;

  /*! \brief Create a camera centered at the origin */
  Camera();

  /*! \brief Create a camera at a specific position with a specific rotation */
  Camera(float px, float py, float pz, float dx, float dy, float dz);

  /*! \brief Set the camera's position and rotation */
  void SetPos(float px, float py, float pz, float dx, float dy, float dz);
};
}  // namespace rpg