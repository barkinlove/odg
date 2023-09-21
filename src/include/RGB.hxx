#pragma once
#include <cstdint>

struct RGB
{
  float red;
  float green;
  float blue;
};

static_assert(sizeof(RGB) == 12);
