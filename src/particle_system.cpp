#include <particle_system.h>
#include <shader.h>

using std::vector;
namespace rpg {

/*! \brief Creates a position array from an array of particles */
inline vector<GLfloat> CreatePositionArray(const vector<Particle>& particles) {
  std::vector<GLfloat> pos_arr(particles.size() * 3);
  for (int i = 0; i < particles.size(); i++) {
    const int offset = i * 3;
    const Particle& particle = particles[i];
    pos_arr[offset] = particle.pos.x;
    pos_arr[offset + 1] = particle.pos.y;
    pos_arr[offset + 2] = particle.pos.z;
  }

  return pos_arr;
}

/*! \brief Creates a color array from an array of particles */
inline vector<GLfloat> CreateColorArray(const vector<Particle>& particles) {
  std::vector<GLfloat> color_arr(particles.size() * 3);

  for (int i = 0; i < particles.size(); i++) {
    const int offset = i * 3;
    const Particle& particle = particles[i];
    color_arr[offset] = particle.color.r;
    color_arr[offset + 1] = particle.color.g;
    color_arr[offset + 2] = particle.color.b;
  }

  return color_arr;
}

Particle::Particle(glm::vec3 pos, glm::vec3 color) {
  this->pos = pos;
  this->color = color;
  this->velocity = glm::vec3{0, 0, 0};
}

void ParticleEngine::GenerateBuffers() {
  // Position Buffer
  glGenBuffers(1, &this->position_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->position_vbo);

  // Color Buffer
  glGenBuffers(1, &this->color_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
}

ParticleEngine::ParticleEngine() {
  // Hardcode points for now
  this->particles = std::vector<Particle>{
      Particle(glm::vec3(0, 0, 1), glm::vec3(255, 0, 0)),
      Particle(glm::vec3(0, 1, 0), glm::vec3(0, 255, 0)),
      Particle(glm::vec3(1, 0, 0), glm::vec3(0, 0, 255)),
      Particle(glm::vec3(-1, 0, 0), glm::vec3(255, 0, 255)),
      Particle(glm::vec3(0, -1, 0), glm::vec3(0, 255, 255)),
      Particle(glm::vec3(0, 0, -1), glm::vec3(255, 255, 255)),
  };

  this->shader = LoadShaders(this->shader_path);

  this->GenerateBuffers();
}

void ParticleEngine::FillBuffers() {
  const auto pos_arr = CreatePositionArray(this->particles);
  glBindBuffer(GL_ARRAY_BUFFER, this->position_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * pos_arr.size(),
               pos_arr.data(), GL_STREAM_DRAW);

  const auto color_arr = CreateColorArray(this->particles);
  glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * color_arr.size(),
               color_arr.data(), GL_STREAM_DRAW);
}

void ParticleEngine::Draw() {
  // Update every frame for now
  // this->FillBuffers();

  glUseProgram(this->shader.program_id);

  const auto pos_arr = CreatePositionArray(this->particles);
  glBindBuffer(GL_ARRAY_BUFFER, this->position_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * pos_arr.size(),
               pos_arr.data(), this->draw_type);

  const auto color_arr = CreateColorArray(this->particles);
  glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * color_arr.size(),
               color_arr.data(), this->draw_type);

  glEnableVertexAttribArray(this->shader.pos_attr);
  glEnableVertexAttribArray(this->shader.color_attr);

  glBindBuffer(GL_ARRAY_BUFFER, this->position_vbo);
  glVertexAttribPointer(this->shader.pos_attr, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, this->color_vbo);
  glVertexAttribPointer(this->shader.color_attr, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_POINTS, 0, particles.size());

  glDisableVertexAttribArray(this->shader.pos_attr);
  glDisableVertexAttribArray(this->shader.color_attr);
}

void ParticleEngine::SetCameraPosition(glm::mat4& MVP) {
  glUniformMatrix4fv(this->shader.mvp, 1, GL_FALSE, &(MVP[0][0]));
}

//~ParticleEngine(){

}  // namespace rpg