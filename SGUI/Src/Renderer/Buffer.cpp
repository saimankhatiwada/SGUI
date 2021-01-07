
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGlBuffer.h"

namespace SGUI
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGlVertexBuffer>(size);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGlVertexBuffer>(vertices, size);
		}
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGlIndexBuffer>(indices, size);
		}
		return nullptr;
	}
}