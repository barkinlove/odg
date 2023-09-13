#pragma once
#include <nlohmann/json.hpp>

class Config final
{
public:
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;

  template<typename T>
  static T get(std::string_view field)
  {
    return instance().m_content.at(field).get<T>();
  }

  static bool has(std::string_view field)
  {
    return instance().m_content.find(field) != instance().m_content.end();
  }

private:
  static const Config& instance();

private:
  Config();
  ~Config();

private:
  nlohmann::json m_content;
};
