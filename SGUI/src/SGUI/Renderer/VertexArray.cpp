#include "hzpch.h"
#include "SGUI/Renderer/VertexArray.h"

#include "SGUI/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SGUI {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
