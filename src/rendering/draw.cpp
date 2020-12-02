#include <rendering/draw.h>

#include <GL\glew.h>

namespace rpg::rendering {
void FillBuffer(const float* vertices,
                int num_elements,
                int vbo_id,
                int attribute_id) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_elements, vertices,
               GL_STREAM_DRAW);
  glVertexAttribPointer(attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void ResizeBuffer(int vbo_id, int attribute_id, int size) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, nullptr, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

float* MapBuffer(int vbo_id) {
  // Bind the buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  // map it and return the pointer
  return reinterpret_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

float* MapBuffer(int vbo_id, int num_elements) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

  return reinterpret_cast<float*>(
      glMapBufferRange(GL_ARRAY_BUFFER, 0, num_elements, GL_MAP_WRITE_BIT));
}

void UnmapBuffer(int vbo_id) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glUnmapBuffer(GL_ARRAY_BUFFER);
}

void EnableVertexAttribute(int vertex_attribute) {
  glEnableVertexAttribArray(vertex_attribute);
}
void DisableVertexAttribute(int vertex_attribute) {
  glDisableVertexAttribArray(vertex_attribute);
}

void UseProgram(int program_id) {
  glUseProgram(program_id);
}
void DrawPoints(int num) {
  glDrawArrays(GL_POINTS, 0, num);
}
}  // namespace rpg::rendering