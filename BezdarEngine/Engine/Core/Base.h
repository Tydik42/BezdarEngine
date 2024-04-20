#pragma once

#define BIT(x) (1 << x)

#define BZ_EXPAND_MACRO(x) x
#define BZ_STRINGIFY_MACRO(x) #x

#define BZ_DEBUGBREAK() __debugbreak()

#define BZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
