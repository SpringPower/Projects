#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include "assertions.hpp"

typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#define LOG(pszMessage) std::cerr<<(pszMessage)<<std::endl

#define UNREFERNCED_PARAMETER(ptParam) (void)(ptParam)

#endif // COMMON_HPP
