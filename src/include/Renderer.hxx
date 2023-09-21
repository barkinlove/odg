#pragma once
#include "Model.hxx"
#include "Shader.hxx"
#include <SDL_video.h>
#include <filesystem>
#include <vector>

class Game;

class Renderer final
{
public:
  Renderer(Game& game);
  ~Renderer();

  void main_loop();

private:
  void render();
  void init();
  size_t load_shaders(std::filesystem::path path);
  void build_shaders();
  void compile_shaders();
  void compile_shader(const Shader& shader);
  void destroy_shaders();
  void destroy_shader(const Shader& shader);
  void init_shaders();

private:
  Game& m_game;
  SDL_GLContext m_glContext;
  std::vector<Shader> m_shaders;
  GLuint m_shaderProgram;

  // make them object later
  std::vector<Model> m_models;
};
