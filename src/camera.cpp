#include <camera.h>

#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <numbers>
#include <utils.h>

using std::numbers::pi;
namespace rpg {
inline glm::vec3 ComputeRightAngle(float horizontal_angle) {
  return glm::vec3(sin(horizontal_angle - (pi / 2.0f)), 0,
                   cos(horizontal_angle - (pi / 2.0f)));
}

inline glm::vec3 ComputeDirection(float vertical_angle,
                                  float horizontal_angle) {
  return glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
                   sin(vertical_angle),
                   cos(vertical_angle) * cos(horizontal_angle));
}

Camera::Camera() {
  this->SetPos(0, 0, 0, 0, 0, -1);
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
  this->UpdateMatricies();
}

void Camera::UpdateMatricies() {
  const glm::vec3 right = ComputeRightAngle(this->horizontal_angle);
  const glm::vec3 direction =
      ComputeDirection(this->vertical_angle, this->horizontal_angle);
  const glm::vec3 up = glm::cross(right, direction);

  this->perspective_matrix =
      glm::perspective(glm::radians(this->fov), Globals::CalculateAspectRatio(),
                       this->near_plane, this->far_plane);
  this->view_matrix = glm::lookAt(this->pos, direction + this->pos, up);
}

const glm::mat4& Camera::GetPerspectiveMatrix() const {
  return this->perspective_matrix;
}

const glm::mat4& Camera::GetViewMatrix() const {
  return this->view_matrix;
}

glm::mat4 Camera::CalculateMVP() const {
  const glm::mat4 model_matrix(1.0);
  return this->perspective_matrix * this->view_matrix * model_matrix;
}

void Camera::Move(const glm::vec2& position_change,
                  const glm::vec2& direction_change) {
  this->pos += (ComputeDirection(this->vertical_angle, this->horizontal_angle) *
                position_change.y);
  this->pos += (ComputeRightAngle(this->horizontal_angle) * position_change.x);

  this->horizontal_angle += direction_change.x;
  this->vertical_angle += direction_change.y;

  vertical_angle = std::clamp(vertical_angle, -3.14f / 2, 3.14f / 2);

  UpdateMatricies();
}

}  // namespace rpg