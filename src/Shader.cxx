#include "Shader.hxx"
#include <array>
#include <string_view>

Shader::Shader(const GLuint type,
               const std::string& name,
               const std::string& src,
               size_t count)
  : m_object(glCreateShader(type))
  , m_name(name)
  , m_src(src)
{
  std::array<const char*, 1> rawSrcs = { m_src.data() };
  std::array<GLint, 1> lengths = { static_cast<GLint>(m_src.size()) };
  glShaderSource(m_object, count, rawSrcs.data(), lengths.data());
};
