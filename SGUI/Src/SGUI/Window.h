#pragma once
#include "SGPCH.h"
#include "Events/Event.h"

namespace SGUI
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;
		WindowProps(const std::string title = "Synthesia(2D)", unsigned int width = 1280, unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{

		}
	};

	class Window
	{
	public:
		using EventCallBackFnc = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallBack(const EventCallBackFnc& callback) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
