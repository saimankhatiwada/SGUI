#include "Synthesia2D.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Synthesia2D::Synthesia2D() :
	Layer("Synthesia2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f,0.3f,0.8f,1.0f }), m_SquareColor1({ 0.8f,0.2f,0.3f,1.0f })
{

}

void Synthesia2D::OnAttach()
{
	SG_PROFILE_FUNCTION();

	m_Texture = SGUI::Texture2D::Create("Assets/Image/Checkerboard.png");
	SGUI::FramebufferSpecification spec;
	spec.Height = 1280;
	spec.Width = 720;
	m_FrameBuffer = SGUI::Framebuffer::Create(spec);
}

void Synthesia2D::OnDetach()
{
	SG_PROFILE_FUNCTION();

}

void Synthesia2D::OnUpdate(SGUI::TimeSteps ts)
{
	SG_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);
	

	{
		SG_PROFILE_SCOPE("Synthesia2D::RenderPrep");
		SGUI::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SGUI::RenderCommand::Clear();
	}

	{
		SG_PROFILE_SCOPE("Synthesia2D::RenderDraw");
		SGUI::Renderer2D::BeginScene(m_CameraController.GetCamera());
		SGUI::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		SGUI::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		SGUI::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		SGUI::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
		SGUI::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, m_Texture, 20.0f);
		SGUI::Renderer2D::EndScene();

		SGUI::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f,0.4f,(y + 5.0f) / 10.0f,0.5f };
				SGUI::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
			}
		}
		SGUI::Renderer2D::EndScene();
	}
}

void Synthesia2D::OnEvent(SGUI::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Synthesia2D::OnImguiRender()
{
	SG_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	auto stats = SGUI::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
