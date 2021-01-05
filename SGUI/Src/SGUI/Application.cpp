#include "SGPCH.h"
#include "Application.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

namespace SGUI
{
#define  BIND_EVENT_FNC(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;



	Application::Application():
		m_TimesStep(0.0f)
	{
		SG_PROFILE_FUNCTION();

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FNC(OnEvent));

		Renderer::Init();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);


	}

	Application::~Application()
	{
		
	}

	void Application::OnEvent(Event& e)
	{
		SG_PROFILE_FUNCTION();

		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FNC(OnWindowClose));
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FNC(OnWindowResize));

		for (std::vector<Layer*>::iterator it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		SG_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		SG_PROFILE_FUNCTION();

		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		SG_PROFILE_SCOPE("Application::Run");

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			m_TimesStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					SG_PROFILE_SCOPE("Layers OnUpdate");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(m_TimesStep);
					}
				}

				m_ImGuiLayer->Begin();
				{
					SG_PROFILE_SCOPE("Layers Stack OnImguiRender");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnImguiRender();
					}
				}
				m_ImGuiLayer->End();
			}
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		SG_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}
