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
		SGUI::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f,0.8f }, m_SquareColor);
		SGUI::Renderer2D::DrawRotatedQuad({ 0.5f,-0.5f }, { 0.5f,0.75f }, 90.0f, m_SquareColor1);
		SGUI::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, m_Texture);
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
	ImGui::Begin("Properties Panel");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Square Color1", glm::value_ptr(m_SquareColor1));
	ImGui::End();
}
