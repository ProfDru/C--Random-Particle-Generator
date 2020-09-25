#pragma once
#include <shader.h>
#include <GL/glew.h>

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace rpg {
struct Particle {
  glm::vec3 pos;
  glm::vec3 velocity;
  glm::vec3 color;
  float lifetime;

  Particle(glm::vec3 pos, glm::vec3 color);
};

class ParticleEngine {
  static const GLenum draw_type = GL_STREAM_DRAW;
  inline static const std::string shader_path = "shaders/particle";
  Shader shader;
  glm::vec3 pos = {0, 0, 0};

  std::vector<Particle> particles;

  GLuint position_vbo;
  GLuint color_vbo;
  const GLfloat particle_size = 5.0f;

  int max_patricles = 10000;
  float particle_lifetime = 5.0f;

 private:
  /*! \brief Create the buffers we need for rendering*/
  void GenerateBuffers();

  /*! \brief Update the position and color of particles on the GPU. */
  void FillBuffers();

 public:
  /*! \brief Construct the particle engine */
  ParticleEngine();

  /*! \brief Draw all particles, */
  void Draw();

  /*! \brief Update all particles */
  void Update();

  /*! \brief Set the camera position for the particle effect */
  void SetCameraPosition(glm::mat4& MVP);

  //~ParticleEngine();
};
}  // namespace rpg