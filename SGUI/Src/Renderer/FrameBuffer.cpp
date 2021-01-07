#include "FrameBuffer.h"
#include "Platform/OpenGl/OpenGlFrameBuffer.h"
#include "Renderer/Renderer.h"

namespace SGUI
{

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGlFramebuffer>(spec);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}