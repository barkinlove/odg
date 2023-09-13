#pragma once
#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>
#include <filesystem>
#include <fstream>
#include <string>

class ShaderFactory;

class Shader
{
  friend class ShaderFactory;

public:
  std::string_view get_name() const noexcept { return m_name; }
  std::string_view get_src() const noexcept { return m_src; }
  GLuint get_object() const noexcept { return m_object; };

private:
  Shader(const GLuint type,
         const std::string& name,
         const std::string& src,
         size_t count);

private:
  GLuint m_object;
  std::string m_name;
  std::string m_src;
};
