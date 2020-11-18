#pragma once
#include <rendering\shader.h>

#include <vector>
#include <cassert>
#include <concepts>
#include <execution>

namespace rpg::rendering {

/*! \brief Bind the buffer, then set the attribute pointer */
void FillBuffer(const float* vertices,
                int num_elements,
                int vbo_id,
                int attribute_id);

/*! \brief Unmap prior ptr, map the new ptr. */
float* MapBuffer(int vbo_id);
float* MapBuffer(int vbo_id, int num_elements);
void ResizeBuffer(int vbo_id, int attribute_id, int size);
void UnmapBuffer(int vbo_id);

void EnableVertexAttribute(int vertex_attribute);
void DisableVertexAttribute(int vertex_attribute);
void UseProgram(int program_id);
void DrawPoints(int num);

template <typename T>
concept mappable_entity = requires(T e) {
  { e.MaxVertices() }
  ->std::integral;
};

template <typename T>
inline const std::vector<float>& GetBufferFromAttribute(
    T& ent,
    const ShaderAttribute& attr) {
  // Fill the buffer with the asked for information
  switch (attr.T) {
    case (ShaderAttribute::type::vertex):
      return ent.GetVertexBuffer();
      break;
    case (ShaderAttribute::type::color):
      return ent.GetColorBuffer();
      break;
    default:
      assert(false);
      break;
  }
}

/*! \brief Set up attribute to be drawn next draw call */
template <typename T>
inline void HandleAttribute(T& ent, ShaderAttribute& attr) {
  // Get a reference to the vector containing buffer info to insert
  const std::vector<float>& buffer_to_insert =
      GetBufferFromAttribute(ent, attr);

  fill_or_map_buffer(ent, attr, buffer_to_insert);
}

inline void fill_or_map_buffer(const mappable_entity auto& ent,
                               ShaderAttribute& attr,
                               const std::vector<float>& buffer_to_insert) {
  const int max_vertices = ent.MaxVertices();
  const int num_vertices = ent.NumVertices();
  // If the number of elements is larger than before, create a new buffer
  if (max_vertices != attr.buffer_size) {
    ResizeBuffer(attr.vbo, attr.id, max_vertices);
    attr.buffer_size = max_vertices;
  }

  float* buffer_ptr = MapBuffer(attr.vbo, num_vertices);
  std::copy_n(std::execution::par_unseq, buffer_to_insert.begin(), num_vertices,
              buffer_ptr);
  UnmapBuffer(attr.vbo);
}

template <typename T>
inline void fill_or_map_buffer(const T& ent,
                               ShaderAttribute& attr,
                               const std::vector<float>& buffer_to_insert) {
  FillBuffer(buffer_to_insert.data(), ent.NumVertices(), attr.vbo, attr.id);
}

template <typename T>
inline void Draw(T& ent, Shader& shader) {
  // Fill buffers and enable each attribute
  UseProgram(shader.get_program_id());

  for (auto& attr : shader.attributes)
    HandleAttribute(ent, attr);

  // Draw points
  DrawPoints(ent.NumVertices() / 3);
}

}  // namespace rpg::rendering