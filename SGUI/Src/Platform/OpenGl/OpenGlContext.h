#pragma once
#include "Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace SGUI
{
	class OpenGlContext :public GraphicsContext
	{
	public:
		OpenGlContext(GLFWwindow* WindowHandle);

		void Init();
		void SwapBuffers();
	private:
		GLFWwindow* m_WindowHandle;
	};
}
