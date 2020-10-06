#pragma once

#include <string>

namespace rpg::rendering {

int LoadShaders(const std::string& vertex_path,
                const std::string& fragment_path);

/*! \brief Load the fragment and vertex shaders at the given path

        \param path path to the vertex/fragment shader pair withut any
   extension. i.e. `shaders/particle` would load shaders/particle.frag and
   shaders.particle.vert

        \returns program_id of the new shader after compilation

        \throws std::runtime_error File could not be found
        \throws std::invalid_argument File could be found but did not compile
   into a valid shader
*/
int LoadShaders(const std::string& path);

int GetUniformID(int program_id, const std::string& uniform_name);

int GetAttributeID(int program_id, const std::string& attribute_name);

/*! \brief Generate a buffer and return the ID of it */
int GenBuffer();

/*! \brief Set the uniform of a shader */
void SetUniformMatrix(int uniform_id, const float* matrix_start);

/*! \brief Set the value of a uniform vector2f */
void SetUniformVector2f(int uniform_id, float x, float y);

}  // namespace rpg::rendering
