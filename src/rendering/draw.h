#pragma once
#include <rendering\shader.h>

#include <vector>
#include <cassert>

namespace rpg::rendering {

/*! \brief Bind the buffer, then set the attribute pointer */
void FillBuffer(const float* vertices,
                int num_elements,
                int vbo_id,
                int attribute_id);
void EnableVertexAttribute(int vertex_attribute);
void DisableVertexAttribute(int vertex_attribute);
void UseProgram(int program_id);
void DrawPoints(int num);

/*! \brief Set up attribute to be drawn next draw call */
template <typename T>
inline void HandleAttribute(T& ent, const ShaderAttribute& attr) {
  // Enable the vertex attribute for this shader
  const int attr_id = attr.id;
  EnableVertexAttribute(attr.id);

  // Fill the buffer with the asked for information
  switch (attr.T) {
    case (ShaderAttribute::type::vertex): {
      const std::vector<float>& vertex_buffer = ent.GetVertexBuffer();
      const int num_vertices = ent.NumVertices();

      FillBuffer(vertex_buffer.data(), num_vertices, attr.vbo, attr_id);
      break;
    }
    case (ShaderAttribute::type::color): {
      const std::vector<float>& color_buffer = ent.GetColorBuffer();
      const int num_vertices = ent.NumVertices();

      FillBuffer(color_buffer.data(), num_vertices, attr.vbo, attr_id);
      break;
    }
    default:
      assert(false);
      break;
  }
}

template <typename T>
inline void Draw(T& ent, const Shader& shader) {
  // Fill buffers and enable each attribute
  UseProgram(shader.get_program_id());

  for (const auto& attr : shader.attributes)
    HandleAttribute(ent, attr);

  // Draw points
  DrawPoints(ent.NumVertices());

  // Disable all attributes
  for (const auto& attr : shader.attributes)
    DisableVertexAttribute(attr.id);
}

}  // namespace rpg::rendering