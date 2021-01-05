
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGlTexture.h"

namespace SGUI
{

	SGUI::Ref<SGUI::Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGlTexture2D>(width, height);
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGlTexture2D>(path);
		}
		return nullptr;
	}

}