
#include "OpenGlContext.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "SGUI/Log.h"
#include "PerformanceVisualizer/RuntimeVisualizer.h"

namespace SGUI
{
	OpenGlContext::OpenGlContext(GLFWwindow* WindowHandle):
		m_WindowHandle(WindowHandle)
	{

	}

	void OpenGlContext::Init()
	{
		SG_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SG_CORE_INFO("OpenGl Info:");
		SG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		SG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		SG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGlContext::SwapBuffers()
	{
		SG_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}