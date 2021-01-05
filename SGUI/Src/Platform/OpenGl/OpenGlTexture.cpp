#include "SGPCH.h"
#include "OpenGlTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace SGUI
{
	OpenGlTexture2D::OpenGlTexture2D(const std::string& path):
		m_Path(path)
	{
		SG_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1); 
		stbi_uc* data = nullptr;
		{
			SG_PROFILE_SCOPE(" stbi_load - OpenGlTexture2D::OpenGlTexture2D(const std::string& path) ");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		SG_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalformat = 0, dataformat = 0;
		if (channels == 4)
		{
			internalformat = GL_RGBA8;
			dataformat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalformat = GL_RGBA8;
			dataformat = GL_RGB;
		}

		m_InternalFormat = internalformat;
		m_DataFormat = dataformat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalformat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataformat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	}

	OpenGlTexture2D::OpenGlTexture2D(uint32_t width, uint32_t height):
		m_Width(width),m_Height(height)
	{
		SG_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGlTexture2D::~OpenGlTexture2D()
	{
		SG_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGlTexture2D::SetData(void* data, uint32_t size)
	{
		SG_PROFILE_FUNCTION();

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGlTexture2D::Bind(uint32_t slot) const
	{
		SG_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}
}