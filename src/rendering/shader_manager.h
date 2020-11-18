#pragma once
#include <rendering\shader.h>

#include <vector>
#include <unordered_map>
#include <string>
namespace rpg::rendering {

class ShaderManager {
 private:
  std::vector<Shader> shaders;  //< An array of shaders ordered by ID
  std::unordered_map<std::string, int>
      name_map;                             //< Maps Shader name to shader id
  std::unordered_map<int, int> entity_map;  //< Maps entity_id to shader id

  /*! \brief Determine whether or not this shader exists in the map */
  bool HasShader(int shader_id) const;

  /*! \brief Determine whether or not this shader exists in the map */
  bool HasShader(const Shader& shader) const;

  /*! \brief Compile a shader and add it to the internal store */
  void CompileShader(Shader& Shader);

 public:
  /*! \brief Start a new shader manager and do nothing */
  ShaderManager();

  /*! \brief Register a shader to a specific object*/
  void RegisterShader(int object_id, Shader& shader);

  /*! \brief Ge ta reference to the shader at a given ID */
  Shader& GetShader(int shader_id);

  /*! \brief Get the id of the shader assigned to a specific entity */
  Shader& GetShaderforObject(int ent_id);

  /*! \brief Update the MVP for every shader that needs it */
  void UpdateMVP(const float* MVP_ptr);

  /*! \brief Update the screen X/Y for every shader that needs it */
  void UpdateScreenXY(float screen_x, float screen_y);
};
}  // namespace rpg::rendering