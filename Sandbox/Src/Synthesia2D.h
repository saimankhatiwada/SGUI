#pragma once
#include "SGUI.h"

class Synthesia2D : public SGUI::Layer
{
public:
	Synthesia2D();
	virtual ~Synthesia2D() = default;
	void OnAttach();
	void OnDetach();
	void OnUpdate(SGUI::TimeSteps ts) override;
	void OnEvent(SGUI::Event& event) override;
	void OnImguiRender() override;
private:
	SGUI::Ref<SGUI::VertexArray> m_SquareVertexArray;
	SGUI::OrthographicCameraController m_CameraController;
	SGUI::Ref<SGUI::Texture2D> m_Texture;
	SGUI::Ref<SGUI::Shader> m_SquareShader;
	SGUI::Ref<SGUI::Framebuffer> m_FrameBuffer;
	glm::vec4 m_SquareColor;
	glm::vec4 m_SquareColor1;
};