#include <particle_system.h>

namespace rpg {
ParticleEngine::ParticleEngine() {

  // Hardcode points for now
  this->points = std::vector<glm::vec3>{
      {0, 0, 0}, {0.1, 0.1, 0.1}, {0.12, 0.2, 0.2}, {-1, -1, -1}, {-2, -2, -2}};

  glGenBuffers(1, &this->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
               points.data(), GL_STATIC_DRAW);
}

void ParticleEngine::Draw() {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_POINTS, 0, points.size());
  glDisableVertexAttribArray(0);
}

//~ParticleEngine(){
///}

}  // namespace rpg