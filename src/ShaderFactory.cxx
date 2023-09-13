#include "ShaderFactory.hxx"

Shader ShaderFactory::Create(GLuint type,
                             const std::string& name,
                             const std::string& src,
                             size_t count)
{
  return { type, name, src, count };
}
