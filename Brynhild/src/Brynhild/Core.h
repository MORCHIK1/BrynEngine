#pragma once

#ifdef BRYN_PLATFORM_WINDOWS
  #ifdef BRYN_BUILD_DLL
    #define BRYN_API __declspec(dllexport)
  #else
    #define BRYN_API __declspec(dllimport)
  #endif
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

#define FMT_HEADER_ONLY