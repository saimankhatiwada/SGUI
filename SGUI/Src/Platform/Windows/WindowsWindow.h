#pragma once
#include "SGUI/Window.h"
#include "SGUI/Events/ApplicationEvent.h"
#include "SGUI/Events/MouseEvent.h"
#include "SGUI/Events/KeyEvent.h"
#include "GLFW/glfw3.h"
#include "Renderer/GraphicsContext.h"

namespace SGUI
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallBack(const EventCallBackFnc& callback) override {  m_Data.EventCallBack = callback; }
		void SetVsync(bool enabled) override;
		bool IsVsync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool Vsync;
			EventCallBackFnc EventCallBack;
		};

		WindowData m_Data;

	};
}