#pragma once

#include <memory>

#include "SGUI/Core/PlatformDetection.h"

#ifdef SG_DEBUG
	#if defined(SG_PLATFORM_WINDOWS)
		#define SG_DEBUGBREAK() __debugbreak()
	#elif defined(SG_PLATFORM_LINUX)
		#include <signal.h>
		#define SG_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define SG_ENABLE_ASSERTS
#else
	#define SG_DEBUGBREAK()
#endif

#define SG_EXPAND_MACRO(x) x
#define SG_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define SG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace SGUI {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "SGUI/Core/Log.h"
#include "SGUI/Core/Assert.h"
