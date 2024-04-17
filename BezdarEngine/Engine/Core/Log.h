#pragma once
#include "memory"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"


// TODO: fix spdlog
namespace BZEngine
{
class Log
{
public:
    static void Init();
    static std::shared_ptr<spdlog::logger>& GetCoreLogger();
    static std::shared_ptr<spdlog::logger>& GetClientLogger();

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
}


// Core log macros
#define BZ_CORE_TRACE(...)    ::BZEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BZ_CORE_INFO(...)     ::BZEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BZ_CORE_WARN(...)     ::BZEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BZ_CORE_ERROR(...)    ::BZEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BZ_CORE_CRITICAL(...) ::BZEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BZ_TRACE(...)         ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BZ_INFO(...)          ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define BZ_WARN(...)          ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BZ_ERROR(...)         ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define BZ_CRITICAL(...)      ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)