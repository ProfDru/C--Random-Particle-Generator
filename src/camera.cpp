#include <camera.h>

namespace rpg {
Camera::Camera() {
  this->SetPos(0, 0, 0, 0, 0, 0);
}

Camera::Camera(float px, float py, float pz, float dx, float dy, float dz) {
  this->SetPos(px, py, pz, dx, dy, dz);
}

void Camera::SetPos(float px,
                    float py,
                    float pz,
                    float dx,
                    float dy,
                    float dz) {
  this->pos = glm::vec3{px, py, pz};
  this->rot = glm::vec3{dx, dy, dz};
}

}  // namespace rpg