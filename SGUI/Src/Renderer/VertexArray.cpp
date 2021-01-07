
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGlVertexArray.h"

namespace SGUI
{
	Ref<VertexArray> VertexArray::Create()
	{
		SG_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGlVertexArray>();
		}
		return nullptr;
	}
}