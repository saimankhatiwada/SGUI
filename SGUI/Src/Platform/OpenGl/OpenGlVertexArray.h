#pragma once
#include "Renderer/VertexArray.h"

namespace SGUI
{
	class OpenGlVertexArray: public VertexArray
	{
	public:
		OpenGlVertexArray();

		virtual ~OpenGlVertexArray();

		void Bind() const;
		void UnBind() const;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer);

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const { return m_VertexBuffer; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}