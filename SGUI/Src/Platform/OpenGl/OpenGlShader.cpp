
#include "OpenGlShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include <fstream>

namespace SGUI
{
	static unsigned int ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
		SG_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGlShader::OpenGlShader(const std::string& name, const std::string& VertexSrc, const std::string& FragmentSrc):
		m_Name(name)
	{
		SG_PROFILE_FUNCTION();

		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = VertexSrc;
		sources[GL_FRAGMENT_SHADER] = FragmentSrc;
		Compile(sources);
	}

	OpenGlShader::OpenGlShader(const std::string& filepath)
	{
		SG_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shadersource = PreProcess(source);
		Compile(shadersource);

		size_t lastslash = filepath.find_last_of("/\\");
		lastslash = lastslash == std::string::npos ? 0 : lastslash + 1;
		size_t lastdot = filepath.rfind('.');
		unsigned long long count = lastdot == std::string::npos ? filepath.size() - lastslash : lastdot - lastslash;
		m_Name = filepath.substr(lastslash, count);
	}

	OpenGlShader::~OpenGlShader()
	{
		SG_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGlShader::Bind() const
	{
		SG_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGlShader::UnBind() const
	{
		SG_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGlShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		SG_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGlShader::SetFloat(const std::string& name, float value)
	{
		SG_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGlShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		SG_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGlShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		SG_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGlShader::SetInt(const std::string& name, int value)
	{
		SG_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGlShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGlShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGlShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGlShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGlShader::UploadUniformFloat(const std::string& name, float values)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, values);
	}

	void OpenGlShader::UploadUniformInt(const std::string& name, int values)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, values);
	}

	void OpenGlShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	std::string OpenGlShader::ReadFile(const std::string& filepath)
	{
		SG_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				SG_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			SG_CORE_ERROR("Couldnot open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<unsigned int, std::string> OpenGlShader::PreProcess(const std::string& source)
	{
		SG_PROFILE_FUNCTION();

		std::unordered_map<unsigned int, std::string> shadersource;
		const char* typeToken = "#type";
		size_t typeTokenlength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			SG_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + typeTokenlength + 1;
			std::string type = source.substr(begin, eol - begin);
			SG_CORE_ASSERT(ShaderTypeFromString(type), "Invalid type specified");

			size_t nextLinepos = source.find_first_not_of("\r\n", eol);
			SG_CORE_ASSERT(nextLinepos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinepos);

			shadersource[ShaderTypeFromString(type)] = source.substr(nextLinepos, pos - (nextLinepos == std::string::npos ? source.size() - 1 : nextLinepos));
		}
		return shadersource;
	}

	void OpenGlShader::Compile(const std::unordered_map<unsigned int, std::string>& shadersource)
	{
		SG_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		std::array<unsigned int, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& keyvalue : shadersource)
		{
			unsigned int type = keyvalue.first;
			const std::string& source = keyvalue.second;
			GLuint Shader = glCreateShader(type);
			const GLchar* sourceCSTR = source.c_str();
			glShaderSource(Shader, 1, &sourceCSTR, 0);
			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(Shader);

				SG_CORE_ERROR("{0}", infoLog.data());
				SG_CORE_ASSERT(false, "Shader compilation error!");
				break;
			}
			glAttachShader(program, Shader);
			glShaderIDs[glShaderIDIndex++] = Shader;
		}
		m_RendererID = program;
		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			SG_CORE_ERROR("{0}", infoLog.data());
			SG_CORE_ASSERT(false, "Shader link error!");
			return;
		}
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
		
	}

	void OpenGlShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGlShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}