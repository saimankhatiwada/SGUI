
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer/RenderComand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace SGUI
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> m_TextureShader;
		Ref<Texture2D> m_WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		SG_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float SquareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

		Ref<SGUI::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		BufferLayout Squarelayout = {
			{ SGUI::ShaderDataType::Float3, "a_Position" },
		    { SGUI::ShaderDataType::Float2 , "a_TexCoord"}
		};
		squareVertexBuffer->SetLayout(Squarelayout);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int SquareIndices[6] = { 0,1,2,2,3,0 };
		Ref<SGUI::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, 6));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

		s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whitetexturedata = 0xffffffff;
		s_Data->m_WhiteTexture->SetData(&whitetexturedata, sizeof(uint32_t));

		s_Data->m_TextureShader = Shader::Create("Assets/Shaders/GameTest.glsl");
		s_Data->m_TextureShader->Bind();
		s_Data->m_TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		SG_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SG_PROFILE_FUNCTION();

		s_Data->m_TextureShader->Bind();
		s_Data->m_TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		SG_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		SG_PROFILE_FUNCTION();

		DrawQuad({ position.x,position.y,0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		SG_PROFILE_FUNCTION();

		s_Data->m_TextureShader->SetFloat4("u_Color", color);
		s_Data->m_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->m_TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor , const glm::vec4& tintColor)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor , const glm::vec4& tintColor)
	{
		SG_PROFILE_FUNCTION();

		s_Data->m_TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->m_TextureShader->SetFloat("m_TillingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)  * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->m_TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		SG_PROFILE_FUNCTION();

		DrawRotatedQuad({ position.x,position.y,0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		SG_PROFILE_FUNCTION();

		s_Data->m_TextureShader->SetFloat4("u_Color", color);
		s_Data->m_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->m_TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		SG_PROFILE_FUNCTION();

		DrawRotatedQuad({ position.x,position.y,0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		SG_PROFILE_FUNCTION();

		s_Data->m_TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->m_TextureShader->SetFloat("m_TillingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->m_TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}