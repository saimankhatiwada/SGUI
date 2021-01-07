#pragma once
#include "Renderer/Shader.h"


namespace SGUI
{
	class OpenGlShader: public Shader
	{
	public:
		OpenGlShader(const std::string& filepath);
		OpenGlShader(const std::string& name, const std::string& VertexSrc, const std::string& FragmentSrc);
		virtual ~OpenGlShader();

		void Bind() const;
		void UnBind() const;
		const std::string& GetName() const { return m_Name; }

		void SetMat4(const std::string& name, const glm::mat4& value);
		void SetFloat(const std::string& name, float value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetInt(const std::string& name, int value);
		void SetIntArray(const std::string& name, int* values, uint32_t count);

		
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& matrix);
		void UploadUniformFloat(const std::string& name, float values);

		void UploadUniformInt(const std::string& name, int values);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<unsigned int, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<unsigned int, std::string>& shadersource);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
