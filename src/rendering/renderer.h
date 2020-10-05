#pragma once

#include <entities/entity.h>
#include <rendering\shader_manager.h>
#include <rendering\draw.h>

#include <concepts>
#include <string>
namespace rpg::rendering {

class Renderer {
 private:
  static ShaderManager shader_manager;

  void HasShader(std::string name);

 public:
  /*! \brief Render the given entity */
  template <typename T>
  inline static void Render(
      const T& ent) requires std::derived_from<T, Entity> {
    const auto& shader = shader_manager.GetShaderforObject(ent.GetID());

    Draw(ent, shader);
  }

  /*! \brief Assign a specific shader to a specific entity. */
  template <typename T>
  inline static void AssignShader(
      const T& ent,
      Shader& shader) requires std::derived_from<T, Entity> {
    shader_manager.RegisterShader(ent.GetID(), shader);
  }

  template <typename T>
  inline static void UpdateMVP(const T& MVP) {
    shader_manager.UpdateMVP(&(MVP[0][0]));
  }
};
}  // namespace rpg::rendering