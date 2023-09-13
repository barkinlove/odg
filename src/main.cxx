#include "Game.hxx"
#include <iostream>
#include <spdlog/spdlog.h>

int main()
{
  try {
    auto& instance = Game::instance();
    instance.run();
    return EXIT_SUCCESS;
  } catch (std::exception& exception) {
    spdlog::critical(exception.what());
    return EXIT_FAILURE;
  }
}
