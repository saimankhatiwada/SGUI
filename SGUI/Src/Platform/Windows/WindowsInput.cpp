
#include "WindowsInput.h"
#include "SGUI/Application.h"
#include "GLFW/glfw3.h"

namespace SGUI
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int KeyCode)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(Window, KeyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int Button)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(Window, Button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::IsGetMouseXImpl()
	{
		std::pair<float,float> PositionMouseX = GetMousePosition();
		return std::get<0>(PositionMouseX);
	}

	float WindowsInput::IsGetMouseYImpl()
	{
		std::pair<float, float> PositionMouseY = GetMousePosition();
		return std::get<1>(PositionMouseY);
	}
	std::pair<float, float> WindowsInput::IsGetMousePositionImpl()
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(Window, &xpos, &ypos);
		return { (float)xpos,(float)ypos };
	}
}