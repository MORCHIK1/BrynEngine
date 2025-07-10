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
