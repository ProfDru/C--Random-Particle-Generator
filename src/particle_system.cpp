#include <particle_system.h>
#include <particle_simulation.h>
#include <shader.h>

using std::vector;
namespace rpg {

/*! \brief Creates a position array from an array of particles */
inline vector<GLfloat> CreatePositionArray(const vector<Particle>& particles) {
  std::vector<GLfloat> pos_arr(particles.size() * 3);
  for (long long unsigned int i = 0; i < particles.size(); i++) {
    const auto offset = i * 3;
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

  for (long long unsigned int i = 0; i < particles.size(); i++) {
    const auto offset = i * 3;
    const Particle& particle = particles[i];
    color_arr[offset] = particle.color.r;
    color_arr[offset + 1] = particle.color.g;
    color_arr[offset + 2] = particle.color.b;
  }

  return color_arr;
}

ParticleEngine::ParticleEngine() {
  // Hardcode points for now
  this->particles = std::vector<Particle>();
}

void ParticleEngine::Update() {
  simulation::simulate_particles(this->particles);
}

std::vector<float> ParticleEngine::GetVertexBuffer() const {
  return CreatePositionArray(particles);
}

std::vector<float> ParticleEngine::GetColorBuffer() const {
  return CreateColorArray(this->particles);
};

int ParticleEngine::NumVertices() const {
  return this->particles.size() * 3;
}
/*
void ParticleEngine::SetCameraPosition(glm::mat4& MVP) {
  glUniformMatrix4fv(this->shader.mvp, 1, GL_FALSE, &(MVP[0][0]));
}
*/

//~ParticleEngine(){

}  // namespace rpg