#pragma once
#include <memory>

#ifdef SG_ENABLE_ASSERTS

#define SG_ASSERT(x,...) {if(!(x)){SG_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
#define SG_CORE_ASSERT(x,...) {if(!(x)){SG_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}

#else
#define SG_ASSERT(x,...)
#define SG_CORE_ASSERT(x,...)

#endif // SG_ENABLE_ASSERTS



#define BIT(x) (1 << x)

#define SG_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

namespace SGUI
{
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
