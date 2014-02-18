#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include "assertions.hpp"

typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#define LOG(pszMessage) std::cerr<<(pszMessage)<<std::endl

#define UNREFERNCED_PARAMETER(ptParam) (void)(ptParam)

#define ARRAY_ENTRIES(atArray) (sizeof(atArray)/sizeof(*atArray))

#define TILE_WIDTH (16)
#define TILE_HEIGHT (16)
#define FONT_WIDTH (8)
#define FONT_HEIGHT (16)

#endif // COMMON_HPP
