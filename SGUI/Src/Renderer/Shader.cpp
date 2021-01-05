
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGlShader.h"

namespace SGUI
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGlShader>(filepath);
		}
		return nullptr;
	}


	Ref<Shader> Shader::Create(const std::string& name, const std::string& VertexSrc, const std::string& FragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGlShader>(name, VertexSrc, FragmentSrc);
		}
		return nullptr;
	}

	void ShaderLibary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SG_CORE_ASSERT(!Exists(name), "Shaders already exists");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibary::Load(const std::string& name, const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibary::Get(const std::string& name)
	{
		SG_CORE_ASSERT(Exists(name), "Shader not found");
		return m_Shaders[name];
	}

	bool ShaderLibary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}