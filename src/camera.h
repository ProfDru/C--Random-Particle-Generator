#pragma once
#include <glm/glm.hpp>

#include <array>

namespace rpg {

/*! \brief A vierpoint for the enging


  \remarks
  The implementation of this class is heavily based on the implementation of
  the "control" header from the LearnOpenGl tutorials, excluding the sections
  about the handling keyboard input.

  Internally the came uses a spherical coordinate system to create view and
  perspective matricies.
  */
class Camera {
 private:
  float horizontal_angle = 3.14f;  // Z-
  float vertical_angle = 0;
  glm::vec3 pos;
  glm::vec3 up;

  glm::mat4 perspective_matrix;
  glm::mat4 view_matrix;

  float near_plane = 0.1f;
  float far_plane = 1000.0f;

  /*! \brief Update view/perspective matricies based on the current position and
   rotation */
  void UpdateMatricies();

 public:
  float fov = 90;

  /*! \brief Create a camera centered at the origin */
  Camera();

  /*! \brief Create a camera at a specific position with a specific rotation */
  Camera(float px,
         float py,
         float pz,
         float horizontal_angle,
         float vertical_angle);

  /*! \brief Set the camera's position and rotation */
  void SetPos(float px,
              float py,
              float pz,
              float horizontal_angle,
              float vertical_angle);

  /*! \brief Move the camera and update it's matricies */
  void Move(const glm::vec2& position_change,
            const glm::vec2& direction_change);

  inline std::array<float, 3> get_pos() const {
    return {pos[0], pos[1], pos[2]};
  };
  std::array<float, 2> get_rotation() const {
    return {horizontal_angle, vertical_angle};
  };
  const glm::mat4& GetPerspectiveMatrix() const;
  const glm::mat4& GetViewMatrix() const;

  glm::mat4 CalculateMVP() const;
};
}  // namespace rpg