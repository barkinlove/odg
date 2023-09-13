#include "Window.hxx"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

Window::Window(std::string title, int32_t width, int32_t height)
  : m_title(title)
  , m_width(width)
  , m_height(height)
{
  // consider moving this to somewhere
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error(
      fmt::format("Unable to initialize video. SDL_Init failed with error: {}",
                  SDL_GetError()));
  }
  spdlog::info("Video has been initialized");
  m_pSelf.reset(SDL_CreateWindow(m_title.c_str(),
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 840,
                                 600,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));
  if (!m_pSelf) {
    throw std::runtime_error(fmt::format(
      "Failed to initialze window. Failed with error: {}", SDL_GetError()));
  }
  m_pSelfSurface = SDL_GetWindowSurface(m_pSelf.get());
  spdlog::info("Window has been initialized");
  if (m_width == 0 || m_height == 0) {
    SDL_GetWindowSize(m_pSelf.get(), &m_width, &m_height);
  }
}

void Window::SDLWindowDeleter::operator()(SDL_Window* pWindow)
{
  SDL_DestroyWindow(pWindow);
}

std::string_view Window::get_title() const noexcept
{
  return m_title;
}

uint32_t Window::get_width() const noexcept
{
  return m_width;
}

uint32_t Window::get_height() const noexcept
{
  return m_height;
}

// consider returning type
SDL_Surface* Window::get_surface() const noexcept
{
  return m_pSelfSurface;
}

void Window::update()
{
  SDL_UpdateWindowSurface(m_pSelf.get());
}

SDL_Window* Window::get_underlying() const noexcept
{
  return m_pSelf.get();
}
