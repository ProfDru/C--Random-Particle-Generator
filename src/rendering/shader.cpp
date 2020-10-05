#include <rendering/shader.h>

using std::string;
using std::vector;
namespace rpg::rendering {

ShaderUniform::ShaderUniform(std::string name, type t) : T(t), name(name) {}
ShaderAttribute::ShaderAttribute(std::string name, type t) : T(t), name(name) {}

Shader::Shader(const std::string& path,
               const std::vector<ShaderUniform>& uniforms,
               const std::vector<ShaderAttribute>& attributes)
    : path(path), uniforms(uniforms), attributes(attributes) {}

}  // namespace rpg::rendering