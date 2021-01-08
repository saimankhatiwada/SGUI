#include "hzpch.h"
#include "SGUI/Core/Window.h"

#ifdef SG_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace SGUI
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef SG_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		SG_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}
