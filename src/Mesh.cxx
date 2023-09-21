#include <GL/glew.h>

#include "Mesh.hxx"
#include "Vertex.hxx"
#include <GL/gl.h>
#include <cstddef>

Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<std::uint32_t> indices,
           std::vector<Texture> texture)
  : m_verticies(std::move(vertices))
  , m_indices(std::move(indices))
  , m_texture(std::move(texture))
{
  setup();
}

void Mesh::setup()
{
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               m_verticies.size() * sizeof(Vertex),
               m_verticies.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               m_indices.size() * sizeof(std::uint32_t),
               m_indices.data(),
               GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, normal)));
  // vertex texture
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, texture)));

  // vertex colors
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, color)));
  glBindVertexArray(0);
}

const std::vector<Vertex>& Mesh::get_vertices() const noexcept
{
  return m_verticies;
}

const std::vector<std::uint32_t>& Mesh::get_indices() const noexcept
{
  return m_indices;
}

const std::vector<Texture>& Mesh::get_texture() const noexcept
{
  return m_texture;
}

std::uint32_t Mesh::get_vao() const noexcept
{
  return m_vao;
}

std::uint32_t Mesh::get_vbo() const noexcept
{
  return m_vbo;
}

std::uint32_t Mesh::get_ebo() const noexcept
{
  return m_ebo;
}
