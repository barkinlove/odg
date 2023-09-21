#pragma once
#include "Model.hxx"
#include <string_view>

class Loader final
{
public:
  static Model load_model(std::string_view path);
};
