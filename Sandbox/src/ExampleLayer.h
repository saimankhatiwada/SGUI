#pragma once

#include "SGUI.h"

class ExampleLayer : public SGUI::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SGUI::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(SGUI::Event& e) override;
private:
	SGUI::ShaderLibrary m_ShaderLibrary;
	SGUI::Ref<SGUI::Shader> m_Shader;
	SGUI::Ref<SGUI::VertexArray> m_VertexArray;

	SGUI::Ref<SGUI::Shader> m_FlatColorShader;
	SGUI::Ref<SGUI::VertexArray> m_SquareVA;

	SGUI::Ref<SGUI::Texture2D> m_Texture, m_ChernoLogoTexture;

	SGUI::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

