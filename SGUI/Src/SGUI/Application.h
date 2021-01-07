#pragma once
#include "SGPCH.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "SGUI/Log.h"
#include "Window.h"
#include "SGUI/LayerStack.h"
#include "SGUI/ImGui/ImGuiLayer.h"
#include "Time/TimeSteps.h"

namespace SGUI
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		void Close();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		TimeSteps m_TimesStep;
		float m_LastFrameTime;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}



