
#include <entities/entity.h>
#include <rendering\shader_manager.h>

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
    const auto& Shader = shader_manager.GetShaderForObject(ent.id);
  }

  /*! \brief Assign a specific shader to a specific entity. */
  template <typename T>
  inline static void AssignShader(
      const T& ent,
      const Shader& shader) requires std::derived_from<T, Entity> {
    shader_manager.RegisterShader(ent.id, shader);
  }
};

}  // namespace rpg::rendering