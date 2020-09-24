#include <GL/glew.h>
#include <string>

#pragma once
namespace rpg {

class Shader {
 public:
  GLuint program_id;

  GLuint pos_attr;
  GLuint color_attr;
  GLuint mvp;

  inline Shader(){};
  Shader(GLuint program_id);
};

/*! \brief Load the fragment and vertex shaders at the given path

        \param path path to the vertex/fragment shader pair withut any
   extension. i.e. `shaders/particle` would load shaders/particle.frag and
   shaders.particle.vert

        \returns ID of the new shader after compilation

        \throws std::runtime_error File could not be found
        \throws std::invalid_argument File could be found but did not compile
   into a valid shader
*/
Shader LoadShaders(const std::string& path);

}  // namespace rpg