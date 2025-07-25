#pragma once

#include "Event.h"
#include "spdlog/fmt/ostr.h"       
#include <type_traits>             

template <typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Brynhild::Event, T>, char>>
  : fmt::ostream_formatter {
};