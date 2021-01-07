
#include "OpenGlRendererAPI.h"
#include "glad/glad.h"

namespace SGUI
{
	void OpenGlRendererAPI::Init()
	{
		SG_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGlRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGlRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGlRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGlRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexcount)
	{
		uint32_t count = indexcount ? vertexArray->GetIndexBuffer()->GetCount() : indexcount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}