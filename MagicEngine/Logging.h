#pragma once
#include "PCH.h"

#ifndef LOG_ENABLED

#define LOG(Text) 

#else

#define LOG(Text) \
{ \
	std::cout << (Text) << std::endl; \
} \

#endif

