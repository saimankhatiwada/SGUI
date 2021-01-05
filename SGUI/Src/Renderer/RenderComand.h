#pragma once

#include "RendererAPI.h"
#include "SGUI/Core.h"

namespace SGUI
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewPort(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}


		inline static void DrawIndexed(Ref<VertexArray>& vertexarray)
		{
			s_RendererAPI->DrawIndexed(vertexarray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}