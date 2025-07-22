#include "Log.h"

namespace Brynhild {
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

  void Log::Init() {
    spdlog::set_pattern("%^[%T] %n%$: %v");

    s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
    s_ClientLogger->set_level(spdlog::level::trace);

    s_CoreLogger = spdlog::stderr_color_mt("BRYNHILD");
    s_CoreLogger->set_level(spdlog::level::trace);
    
  }
}