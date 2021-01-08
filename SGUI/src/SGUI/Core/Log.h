#pragma once

#include "SGUI/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace SGUI {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define SG_CORE_TRACE(...)    ::SGUI::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SG_CORE_INFO(...)     ::SGUI::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SG_CORE_WARN(...)     ::SGUI::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SG_CORE_ERROR(...)    ::SGUI::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SG_CORE_CRITICAL(...) ::SGUI::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SG_TRACE(...)         ::SGUI::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SG_INFO(...)          ::SGUI::Log::GetClientLogger()->info(__VA_ARGS__)
#define SG_WARN(...)          ::SGUI::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SG_ERROR(...)         ::SGUI::Log::GetClientLogger()->error(__VA_ARGS__)
#define SG_CRITICAL(...)      ::SGUI::Log::GetClientLogger()->critical(__VA_ARGS__)
