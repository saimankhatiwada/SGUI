#pragma once

#include "Renderer/RendererAPI.h"
#include "SGUI/Core.h"

namespace SGUI
{
	class OpenGlRendererAPI : public RendererAPI
	{
		void Init();
		void SetClearColor(const glm::vec4& color);
		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void Clear();

		void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}