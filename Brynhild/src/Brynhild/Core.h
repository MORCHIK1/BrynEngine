#pragma once

#ifdef BRYN_PLATFORM_WINDOWS
  #define BRYN_API 
#else
  #error Brynhild only supports Windows!
#endif

#ifdef BRYN_ENABLE_ASSERTS
  #define BRYN_CLIENT_ASSERT(x, ...) { if(!x) { BRYN_CLIENT_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak(); }}
  #define BRYN_CORE_ASSERT(x, ...) { if(!x) { BRYN_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak(); }}
#else
  #define BRYN_CLIENT_ASSERT(x, ...)
  #define BRYN_CORE_ASSERT(x, ...)  
#endif

//#define FMT_HEADER_ONLY

#define BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)