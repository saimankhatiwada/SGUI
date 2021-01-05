
#include "WindowsWindow.h"
#include "glad/glad.h"
#include "Platform/OpenGl/OpenGlContext.h"


namespace SGUI
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		SG_CORE_ERROR("GLFW error {0}:{1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps & props)
	{
		SG_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		SG_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		SG_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		SG_PROFILE_FUNCTION();

		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.Vsync = enabled;
	}

	bool WindowsWindow::IsVsync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::Init(const WindowProps & props)
	{
		SG_PROFILE_FUNCTION();

		m_Data.Title = props.Height;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SG_CORE_INFO("Creating Window {0} ({1},{2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			int Sucess = glfwInit();
			SG_CORE_ASSERT(Sucess, "Could not Initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGlContext(m_Window);
		m_Context->Init();

		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		//set GLFW callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = Width;
			data.Height = Height;


			WindowResizeEvent eventWindowSize(Width, Height);
			data.EventCallBack(eventWindowSize);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent eventWindowClose;
			data.EventCallBack(eventWindowClose);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent eventKeyPress(key, 0);
					data.EventCallBack(eventKeyPress);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent eventKeyRelease(key);
					data.EventCallBack(eventKeyRelease);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent eventKeyPressedRepeat(key, 1);
					data.EventCallBack(eventKeyPressedRepeat);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window,unsigned int KeyCode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(KeyCode);
			data.EventCallBack(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent eventMouseButtonPress(button);
					data.EventCallBack(eventMouseButtonPress);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent eventMouseButtonRelease(button);
					data.EventCallBack(eventMouseButtonRelease);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent eventMouseScroll((float)xOffset, (float)yOffset);
			data.EventCallBack(eventMouseScroll);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent eventMouseCursorPos((float)xPos, (float)yPos);
			data.EventCallBack(eventMouseCursorPos);
		});
	}

	void WindowsWindow::Shutdown()
	{
		SG_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

}