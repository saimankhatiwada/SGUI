#pragma once

#include "SGUI/Core/Base.h"
#include "SGUI/Core/Log.h"
#include <filesystem>

#ifdef SG_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define SG_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HZ##type##ERROR(msg, __VA_ARGS__); HZ_DEBUGBREAK(); } }
	#define SG_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SG_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define SG_INTERNAL_ASSERT_NO_MSG(type, check) SG_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SG_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SG_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SG_INTERNAL_ASSERT_GET_MACRO(...) SG_EXPAND_MACRO( SG_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SG_INTERNAL_ASSERT_WITH_MSG, SG_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define SG_ASSERT(...) SG_EXPAND_MACRO( SG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define SG_CORE_ASSERT(...) SG_EXPAND_MACRO( SG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define SG_ASSERT(...)
	#define SG_CORE_ASSERT(...)
#endif
