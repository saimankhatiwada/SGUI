
#include "OpenGlVertexArray.h"
#include "glad/glad.h"


namespace SGUI
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
				return GL_FLOAT;
			case ShaderDataType::Float2:
				return GL_FLOAT;
			case ShaderDataType::Float3:
				return GL_FLOAT;
			case ShaderDataType::Float4:
				return GL_FLOAT;
			case ShaderDataType::Mat3:
				return GL_FLOAT;
			case ShaderDataType::Mat4:
				return GL_FLOAT;
			case ShaderDataType::Int:
				return GL_INT;
			case ShaderDataType::Int2:
				return GL_INT;
			case ShaderDataType::Int3:
				return GL_INT;
			case ShaderDataType::Int4:
				return GL_INT;
			case ShaderDataType::Bool:
				return GL_BOOL;
		}
		return 0;
	}

	OpenGlVertexArray::OpenGlVertexArray()
	{
		SG_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGlVertexArray::~OpenGlVertexArray()
	{
		SG_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGlVertexArray::Bind() const
	{
		SG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGlVertexArray::UnBind() const
	{
		SG_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGlVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer)
	{
		SG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();
		uint32_t index = 0;
		for (const std::vector<BufferElement>::const_iterator::value_type& element : vertexbuffer->GetLayout())//or use auto after const
		{

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, vertexbuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffer.push_back(vertexbuffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer)
	{
		SG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}
}