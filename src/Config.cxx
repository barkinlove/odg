#include "Config.hxx"
#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>

Config::Config()
{
  auto path = std::filesystem::current_path() / "config.json";
  std::ifstream file{ path };
  if (!file.is_open()) {
    spdlog::info("No config file found.");
  } else {
    m_content = nlohmann::json::parse(file);
  }
}

Config::~Config() = default;

const Config& Config::instance()
{
  static Config s_config;
  return s_config;
}
