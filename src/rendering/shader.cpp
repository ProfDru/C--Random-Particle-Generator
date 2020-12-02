#include <rendering/shader.h>

using std::string;
using std::vector;

static const string vertex_ext = ".vert";
static const string fragment_ext = ".frag";

namespace rpg::rendering {

ShaderUniform::ShaderUniform(std::string name, type t) : T(t), name(name) {}
ShaderAttribute::ShaderAttribute(std::string name, type t)
    : T(t), name(name), buffer_ptr(nullptr) {}

/*! \brief Add an extension to the path if it doesn't have one */
inline string add_path(const string& path, const string& extension) {
  if (path.find(extension) != string::npos) {
    return path;
  } else {
    return path + extension;
  }
}

Shader::Shader(const string& path,
               const vector<ShaderUniform>& uniforms,
               const vector<ShaderAttribute>& attributes,
               bool use_shared_buffers)
    : uniforms(uniforms),
      attributes(attributes),
      use_mapped_buffers(use_shared_buffers) {
  this->fragment_path = add_path(path, fragment_ext);
  this->vertex_path = add_path(path, vertex_ext);
};

Shader::Shader(const string& vertex_path,
               const string& fragment_path,
               const vector<ShaderUniform>& uniforms,
               const vector<ShaderAttribute>& attributes,
               bool use_shared_buffers)
    : uniforms(uniforms), attributes(attributes) {
  this->fragment_path = add_path(fragment_path, fragment_ext);
  this->vertex_path = add_path(vertex_path, vertex_ext);
};

}  // namespace rpg::rendering