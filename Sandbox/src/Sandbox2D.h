#pragma once

#include "SGUI.h"

class Sandbox2D : public SGUI::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SGUI::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(SGUI::Event& e) override;
private:
	SGUI::OrthographicCameraController m_CameraController;
	
	// Temp
	SGUI::Ref<SGUI::VertexArray> m_SquareVA;
	SGUI::Ref<SGUI::Shader> m_FlatColorShader;

	SGUI::Ref<SGUI::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
