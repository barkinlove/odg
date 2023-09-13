#pragma once
#include "Shader.hxx"

class ShaderFactory
{
public:
  static Shader Create(GLuint type,
                       const std::string& name,
                       const std::string& src,
                       size_t count = 1);
};
