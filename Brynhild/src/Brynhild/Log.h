#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Brynhild 
{
  class BRYN_API Log
  {
  private:
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
    static std::shared_ptr<spdlog::logger> s_CoreLogger;

  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

  };
}

#define BRYN_CORE_ERROR(...)         ::Brynhild::Log::GetCoreLogger()->error(__VA_ARGS__);
#define BRYN_CORE_TRACE(...)         ::Brynhild::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define BRYN_CORE_INFO(...)          ::Brynhild::Log::GetCoreLogger()->info(__VA_ARGS__);
#define BRYN_CORE_WARN(...)          ::Brynhild::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define BRYN_CORE_CRITICAL(...)      ::Brynhild::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define BRYN_CLIENT_ERROR(...)       ::Brynhild::Log::GetClientLogger()->error(__VA_ARGS__);
#define BRYN_CLIENT_TRACE(...)       ::Brynhild::Log::GetClientLogger()->trace(__VA_ARGS__);
#define BRYN_CLIENT_INFO(...)        ::Brynhild::Log::GetClientLogger()->info(__VA_ARGS__);
#define BRYN_CLIENT_WARN(...)        ::Brynhild::Log::GetClientLogger()->warn(__VA_ARGS__);
#define BRYN_CLIENT_CRITICAL(...)    ::Brynhild::Log::GetClientLogger()->critical(__VA_ARGS__);