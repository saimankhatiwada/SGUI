#include "hzpch.h"
#include "SGUI/Renderer/GraphicsContext.h"

#include "SGUI/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace SGUI {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
