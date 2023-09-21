#pragma once
#include "Texture.hxx"
#include "Vertex.hxx"
#include <vector>

class Mesh final
{
public:
  Mesh(std::vector<Vertex> verticies,
       std::vector<std::uint32_t> indicies,
       std::vector<Texture> texture);

  const std::vector<Vertex>& get_vertices() const noexcept;
  const std::vector<std::uint32_t>& get_indices() const noexcept;
  const std::vector<Texture>& get_texture() const noexcept;
  std::uint32_t get_vao() const noexcept;
  std::uint32_t get_vbo() const noexcept;
  std::uint32_t get_ebo() const noexcept;

private:
  void setup();

private:
  std::vector<Vertex> m_verticies;
  std::vector<std::uint32_t> m_indices;
  std::vector<Texture> m_texture;
  std::uint32_t m_vao, m_vbo, m_ebo;
};
