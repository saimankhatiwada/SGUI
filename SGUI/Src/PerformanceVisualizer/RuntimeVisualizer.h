#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include "SGUI/Log.h"

namespace SGUI {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct RuntimeVisualizerSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				if (Log::GetCoreLogger()) //case: BeginSession() might be before Log::Init()
				{
					SG_CORE_ERROR("RuntimeVisualizer::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new RuntimeVisualizerSession({ name });
				WriteHeader();
			}
			else
			{
				if (Log::GetCoreLogger()) //case: BeginSession() might be before Log::Init()
				{
					SG_CORE_ERROR("RuntimeVisualizer could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}
	private:
		std::mutex m_Mutex;
		RuntimeVisualizerSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class RuntimeVisualizerTimer
	{
	public:
		RuntimeVisualizerTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~RuntimeVisualizerTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			std::chrono::steady_clock::time_point endTimepoint = std::chrono::steady_clock::now();
			FloatingPointMicroseconds highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			std::common_type_t<std::chrono::microseconds, std::chrono::microseconds> elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace RuntimeVisualizerUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define SG_PROFILE 0
#if SG_PROFILE
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define SG_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define SG_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define SG_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define SG_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define SG_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define SG_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define SG_FUNC_SIG __func__
#else
#define SG_FUNC_SIG "SG_FUNC_SIG unknown!"
#endif

#define SG_PROFILE_BEGIN_SESSION(name, filepath) ::SGUI::Instrumentor::Get().BeginSession(name, filepath)
#define SG_PROFILE_END_SESSION() ::SGUI::Instrumentor::Get().EndSession()
#define SG_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::SGUI::RuntimeVisualizerUtils::CleanupOutputString(name, "__cdecl ");\
											   ::SGUI::RuntimeVisualizerTimer timer##line(fixedName##line.Data)
#define SG_PROFILE_SCOPE_LINE(name, line) SG_PROFILE_SCOPE_LINE2(name, line)
#define SG_PROFILE_SCOPE(name) SG_PROFILE_SCOPE_LINE(name, __LINE__)
#define SG_PROFILE_FUNCTION() SG_PROFILE_SCOPE(SG_FUNC_SIG)
#else
#define SG_PROFILE_BEGIN_SESSION(name, filepath)
#define SG_PROFILE_END_SESSION()
#define SG_PROFILE_SCOPE(name)
#define SG_PROFILE_FUNCTION()
#endif