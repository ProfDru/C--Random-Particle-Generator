#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cassert>
namespace rpg::rendering {

using std::ifstream;
using std::string;

/*! \brief Get a string containing all the characters in a file
    \remarks Taken from a stack overflow post
    https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
*/
inline string ReadFile(const string& fileName) {
  ifstream ifs(fileName.c_str(),
               std::ios::in | std::ios::binary | std::ios::ate);

  if (!ifs.is_open())
    throw std::runtime_error("File could not be found");

  ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  return string(bytes.data(), fileSize);
}

/*! \brief Check to see if a shader compiled correctly. Print a log if it didn't
 */
inline void CheckShader(GLuint shader_id) {
  GLint result = GL_FALSE;
  GLint log_length = 0;

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 0) {
    std::vector<char> error_message(log_length + 1);
    glGetShaderInfoLog(shader_id, log_length, NULL, &error_message[0]);
    printf("SHADER ERROR: %s\n", &error_message[0]);
    assert(log_length < 0);
  }
}

/*! \brief Check to see if a program compiled correctly. Print a log if it
 * didn't
 */
inline void CheckProgram(GLuint program_id) {
  GLint result = GL_FALSE;
  GLint log_length = 0;

  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 0) {
    std::vector<char> error_message(log_length + 1);
    glGetProgramInfoLog(program_id, log_length, NULL, &error_message[0]);
    printf("Program ERROR: %s\n", &error_message[0]);
    assert(log_length < 0);
  }
}

/*! \brief Compile a shader and get the ID that it's assigned */
inline void CompileShader(const std::string& shader_code, GLuint shader_id) {
  char const* code_ptr = shader_code.c_str();
  const GLint num_chars = shader_code.length();

  glShaderSource(shader_id, 1, &code_ptr, &num_chars);
  glCompileShader(shader_id);
  CheckShader(shader_id);
}

/*! \brief Link shaders at frag_id and vert_id into a new program

        \returns The ID of the program resulting from linking vert_id and
   frag_id
*/
inline GLuint LinkShaders(GLuint frag_id, GLuint vert_id) {
  GLuint program_id = glCreateProgram();

  glAttachShader(program_id, vert_id);
  glAttachShader(program_id, frag_id);
  glLinkProgram(program_id);

  CheckProgram(program_id);

  return program_id;
}

int LoadShaders(const std::string& path) {
  string frag_code = ReadFile(path + ".frag");
  string vert_code = ReadFile(path + ".vert");

  if (frag_code.empty() || vert_code.empty())
    throw std::invalid_argument(
        "fragment or vertex filepaths lead to empty files.");

  GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  CompileShader(vert_code, vert_shader_id);
  CompileShader(frag_code, frag_shader_id);

  GLuint program_id = LinkShaders(vert_shader_id, frag_shader_id);

  glDetachShader(program_id, vert_shader_id);
  glDetachShader(program_id, frag_shader_id);
  glDeleteShader(vert_shader_id);
  glDeleteShader(frag_shader_id);

  return program_id;
}

int GetUniformID(int program_id, const string& uniform_name) {
  return glGetUniformLocation(program_id, uniform_name.c_str());
}

int GetAttributeID(int program_id, const string& attribute_name) {
  return glGetAttribLocation(program_id, attribute_name.c_str());
}

int GenBuffer() {
  GLuint buffer_id = -1;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

  return static_cast<int>(buffer_id);
}

void SetUniformMatrix(int uniform_id, const float* matrix_start) {
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE, matrix_start);
}

}  // namespace rpg::rendering