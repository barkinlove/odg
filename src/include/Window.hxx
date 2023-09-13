#pragma once
#include <SDL_video.h>
#include <cstdint>
#include <memory>

class Window final
{
public:
  Window(std::string title, int32_t width = 0, int32_t height = 0);

  std::string_view get_title() const noexcept;
  uint32_t get_width() const noexcept;
  uint32_t get_height() const noexcept;
  SDL_Surface* get_surface() const noexcept;
  SDL_Window* get_underlying() const noexcept;
  void update();

private:
  struct SDLWindowDeleter
  {
    void operator()(SDL_Window* pWindow);
  };

  std::unique_ptr<SDL_Window, SDLWindowDeleter> m_pSelf;
  SDL_Surface* m_pSelfSurface;
  std::string m_title;
  int32_t m_width;
  int32_t m_height;
};
