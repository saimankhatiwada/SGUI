#pragma once
#include "Renderer/Buffer.h"

namespace SGUI
{
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(uint32_t size);
		OpenGlVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGlVertexBuffer();

		void Bind() const;
		void UnBind() const;

		void SetData(const void* data, uint32_t size);

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGlIndexBuffer : public IndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGlIndexBuffer();

		void Bind() const;
		void UnBind() const;

		uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
