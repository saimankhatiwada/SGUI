#pragma once
#include "SGUI.h"

namespace SGUI
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		void OnAttach();
		void OnDetach();
		void OnUpdate(TimeSteps ts) override;
		void OnEvent(Event& event) override;
		void OnImguiRender() override;
	private:
		Ref<VertexArray> m_SquareVertexArray;
		OrthographicCameraController m_CameraController;
		Ref<Texture2D> m_Texture;
		Ref<Shader> m_SquareShader;
		Ref<Framebuffer> m_FrameBuffer;
	};
}

