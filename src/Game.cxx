#include "Game.hxx"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <SDL_opengl.h>

Game::Game()
  : m_window("odg")
  , m_renderer(*this)
{
  spdlog::info("Game class has been initialized");
};

Game::~Game()
{
  SDL_Quit();
  spdlog::info("SDL quit.");
};

void Game::run()
{
  m_renderer.main_loop();
}

const Window& Game::get_window() const noexcept
{
  return m_window;
}

Game& Game::instance()
{
  static Game s_game;
  return s_game;
}
