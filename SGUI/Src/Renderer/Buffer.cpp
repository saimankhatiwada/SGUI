
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGlBuffer.h"

namespace SGUI
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGlVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGlIndexBuffer(indices, size);
		}
		return nullptr;
	}
}