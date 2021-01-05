#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace SGUI
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}


#define  SG_CORE_TRACE(...) ::SGUI::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SG_CORE_INFO(...) ::SGUI::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SG_CORE_WARN(...) ::SGUI::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SG_CORE_ERROR(...) ::SGUI::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SG_CORE_CRITICAL(...) ::SGUI::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define  SG_TRACE(...) ::SGUI::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SG_INFO(...) ::SGUI::Log::GetClientLogger()->info(__VA_ARGS__)
#define SG_WARN(...) ::SGUI::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SG_ERROR(...) ::SGUI::Log::GetClientLogger()->error(__VA_ARGS__)
#define SG_CRITICAL(...) ::SGUI::Log::GetClientLogger()->critical(__VA_ARGS__)
