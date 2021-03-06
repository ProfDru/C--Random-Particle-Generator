#pragma once
#include <string>
#include <vector>
#include <concepts>

namespace rpg::rendering {

struct ShaderUniform {
  enum type { MVP, SCREEN_XY };

  type T;
  std::string name;
  int id = -1;  //< ID of the uniform in the shader. Starts as -1, then is
                // filled when the shader inits

  /*! \brief Create a new shader uniform with the given name and program */
  ShaderUniform(std::string name, type t);

  /*! \brief Initialize this uniform for the given shader.
      \details Tries to load the id if the uniform at *name* for program_id

      \returns False if the uniform did not exist in the shader, and true
     otherwise

   */
  bool Init(int program_id);
};

struct ShaderAttribute {
  enum type { vertex, color };

  type T;
  std::string name;
  int id = -1;
  int vbo = -1;
  int buffer_size = 0;
  float* buffer_ptr;

  ShaderAttribute(std::string name, type t);
};

/*! \brief A GLSL shader that was loaded with a file */
struct Shader {
 private:
  int program_id = -1;
  bool use_mapped_buffers = false;

 public:
  std::string name;
  std::string vertex_path;
  std::string fragment_path;

  std::vector<ShaderUniform> uniforms;
  std::vector<ShaderAttribute> attributes;

  Shader(const std::string& path,
         const std::vector<ShaderUniform>& uniforms,
         const std::vector<ShaderAttribute>& attributes,
         bool use_shared_buffers = false);

  Shader(const std::string& vertex_path,
         const std::string& fragment_path,
         const std::vector<ShaderUniform>& uniforms,
         const std::vector<ShaderAttribute>& attributes,
         bool use_shared_buffers = false);

  inline int get_program_id() const { return program_id; }
  inline void set_program_id(int new_id) { this->program_id = new_id; }
};
}  // namespace rpg::rendering