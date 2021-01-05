#pragma once

#include "Renderer/Texture.h"

namespace SGUI
{
	class OpenGlTexture2D :public Texture2D
	{
	public:
		OpenGlTexture2D(uint32_t width, uint32_t height);
		OpenGlTexture2D(const std::string& path);
		virtual ~OpenGlTexture2D();

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }

		void SetData(void* data, uint32_t size);

		virtual void Bind(uint32_t slot = 0) const;


	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		std::string m_Path;
		unsigned int m_InternalFormat, m_DataFormat;
	};
}
