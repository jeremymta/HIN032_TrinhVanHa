#pragma once
#include <string>
#include "../Utilities/utilities.h"

char* LoadPNG(const std::string& filename, int* width, int* height, int* bpp);