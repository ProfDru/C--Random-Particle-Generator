#include <rendering/shader_manager.h>
#include <rendering/shader_loader.h>
#include <rendering/draw.h>

#include <unordered_map>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cassert>

using std::unordered_map;
using std::vector;
namespace rpg::rendering {

/*! \brief Determine whether a shader has been compiled or not */
bool has_been_compiled(const Shader& shader) {
  return shader.get_program_id() >= 0;
}

ShaderManager::ShaderManager(){};

void ShaderManager::CompileShader(Shader& shader) {
  assert(!has_been_compiled(shader));

  // Compile this shader and get the program ID from opengl
  const int program_id = LoadShaders(shader.vertex_path, shader.fragment_path);
  shader.set_program_id(program_id);

  // Get the ID for all of it's uniforms and attributes
  for (auto& uniform : shader.uniforms)
    uniform.id = GetUniformID(program_id, uniform.name);
  for (auto& attribute : shader.attributes) {
    attribute.id = GetAttributeID(program_id, attribute.name);
    attribute.vbo = GenBuffer();
    EnableVertexAttribute(attribute.id);
  }

  // Add it to our vector and name dictionary
  const int next_id = this->shaders.size();
  shaders.push_back(shader);
  this->name_map.insert({shader.name, next_id});
}

/*! \note Just a test of whether or not the shader exists */
bool ShaderManager::HasShader(int shader_id) const {
  return shader_id < static_cast<int>(shaders.size());
}

/*! \note Just a test of whether or not the shader exists */
bool ShaderManager::HasShader(const Shader& shader) const {
  return this->name_map.count(shader.name) > 0;
}

void ShaderManager::RegisterShader(int object_id, Shader& shader) {
  if (!this->HasShader(shader))
    this->CompileShader(shader);

  const auto shader_id = this->name_map.at(shader.name);

  this->entity_map.insert({object_id, shader_id});
}

Shader& ShaderManager::GetShaderforObject(int ent_id) {
  assert(this->entity_map.count(ent_id) > 0);

  return shaders[this->entity_map.at(ent_id)];
}

void ShaderManager::UpdateMVP(const float* MVP_ptr) {
  for (const auto& shader : this->shaders) {
    UseProgram(shader.get_program_id());
    for (const auto& uniform : shader.uniforms) {
      if (uniform.T == ShaderUniform::type::MVP)
        SetUniformMatrix(uniform.id, MVP_ptr);
    }
  }
}

void ShaderManager::UpdateScreenXY(float screen_x, float screen_y) {
  for (const auto& shader : this->shaders) {
    UseProgram(shader.get_program_id());
    for (const auto& uniform : shader.uniforms) {
      if (uniform.T == ShaderUniform::type::SCREEN_XY)
        SetUniformVector2f(uniform.id, screen_x, screen_y);
    }
  }
}

}  // namespace rpg::rendering