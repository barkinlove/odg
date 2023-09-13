#pragma once
#include "Renderer.hxx"
#include "Window.hxx"

class Game final
{
public:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  static Game& instance();

  const Window& get_window() const noexcept;

  void run();

private:
  Game();
  ~Game();

  void draw_scene();

private:
  Window m_window;
  Renderer m_renderer;
};
