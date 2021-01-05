
#include "Platform/OpenGl/OpenGlShader.h"
#include "imgui.h"
#include "Platform/OpenGl/OpenGlTexture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Synthesia2D.h"
#include "SGUI/EntryPoint.h"

class ExampleLayer : public SGUI::Layer
{
public:
	ExampleLayer()
		:Layer("ExampleLayer"), m_CameraController(1280.0f/720.0f), m_SquareColor({0.2f,0.3f,0.8f})
	{
		m_SquareVertexArray = SGUI::VertexArray::Create();

		float SquareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

		SGUI::Ref<SGUI::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(SGUI::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SGUI::BufferLayout Squarelayout = {
			{ SGUI::ShaderDataType::Float3, "a_Position" },
			{ SGUI::ShaderDataType::Float2, "a_TexCord" }
		};
		squareVertexBuffer->SetLayout(Squarelayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int SquareIndices[6] = { 0,1,2,2,3,0 };
		SGUI::Ref<SGUI::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(SGUI::IndexBuffer::Create(SquareIndices, 6));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		SGUI::Ref<SGUI::Shader> m_SquareShader = m_ShaderLibary.Load("Assets/Shaders/SquareShader.glsl");
		SGUI::Ref<SGUI::Shader> m_TextureShader = m_ShaderLibary.Load("Assets/Shaders/Test.glsl");
		
		m_Texture = SGUI::Texture2D::Create("Assets/Image/Checkerboard.png");

		std::dynamic_pointer_cast<SGUI::OpenGlShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<SGUI::OpenGlShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(SGUI::TimeSteps ts) override
	{
		SG_TRACE("Delta time: {0}s {1}ms", ts.GetSeconds(), ts.GetMilliSecounds());

		m_CameraController.OnUpdate(ts);

		SGUI::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SGUI::RenderCommand::Clear();

		SGUI::Renderer::BeginScene(m_CameraController.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		SGUI::Ref<SGUI::Shader> m_SquareShader = m_ShaderLibary.Get("SquareShader");
		std::dynamic_pointer_cast<SGUI::OpenGlShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<SGUI::OpenGlShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(j * 0.11f, i * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				SGUI::Renderer::Submit(m_SquareVertexArray, m_SquareShader, transform);
			}
		}
		SGUI::Ref<SGUI::Shader> m_TextureShader = m_ShaderLibary.Get("Test");
		m_Texture->Bind();
		SGUI::Renderer::Submit(m_SquareVertexArray, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		SGUI::Renderer::EndScene();
	}

	void OnEvent(SGUI::Event& event) override
	{
		m_CameraController.OnEvent(event);
		if (event.GetEventType() == SGUI::EventType::WindowResize)
		{
			SGUI::WindowResizeEvent& re = (SGUI::WindowResizeEvent&)event;
			//float zoom = (float)re.GetWidth() / 1280.0f;
			//m_CameraController.SetZoomLevel(zoom);
		}
	}

	void OnImguiRender() override
	{
		ImGui::Begin("Change Color");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	SGUI::ShaderLibary m_ShaderLibary;
	SGUI::Ref<SGUI::VertexArray> m_SquareVertexArray;
	SGUI::OrthographicCameraController m_CameraController;
	SGUI::Ref<SGUI::Texture2D> m_Texture;
	glm::vec3 m_SquareColor;

};

class Sandbox: public SGUI::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Synthesia2D());
	}
	~Sandbox()
	{

	}
};

SGUI::Application* SGUI::CreateApplication()
{
	return new Sandbox();
}

