#include "hzpch.h"
#include "SGUI/Renderer/Framebuffer.h"

#include "SGUI/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace SGUI {
	
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

