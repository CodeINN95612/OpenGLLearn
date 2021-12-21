#include "Shader.hpp"

//GL
#include <glad/glad.h>

//std
#include <stdio.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>

static std::string ReadShaderFile(const char* filepath);

namespace GL
{
	Shader::Shader(const char* vertexSource, const char* fragmentSource, uint8_t setThisToZero)
	{
		Init(vertexSource, fragmentSource);
	}

	Shader::Shader(const char* vertexFilepath, const char* fragmentFilepath)
	{
		std::string vertexSource = ReadShaderFile(vertexFilepath);
		std::string fragmentSource = ReadShaderFile(fragmentFilepath);
		Init(vertexSource.c_str(), fragmentSource.c_str());
	}

	Shader::~Shader()
	{
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		glDeleteProgram(m_Program);
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::Init(const char* vertexSource, const char* fragmentSource)
	{
		m_VertexShader = CreateShader(Stage::Vertex, vertexSource);
		m_FragmentShader = CreateShader(Stage::Fragment, fragmentSource);
		CreateProgram();
	}

	uint32_t Shader::CreateShader(Stage stage, const char* source)
	{
		GLuint shader = glCreateShader(GlShaderStageFromStage(stage));
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success != GL_TRUE)
		{
			int logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			char *infoLog = new char[logLength + 1];
			const char* stagestr = "";
			switch (stage)
			{
			case GL::Shader::Stage::Vertex:
				stagestr = "VERTEX";
				break;
			case GL::Shader::Stage::Fragment:
				stagestr = "FRAGMENT";
				break;
			default:
				assert(false);
			}

			glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
			printf("ERROR::SHADER::%s::COMPILATION_FAILED:\n%s", stagestr, infoLog);
			assert(false && "Unable to compile shader, check console");

			delete[] infoLog;
		}
		return shader;
	}

	void Shader::CreateProgram()
	{
		m_Program = glCreateProgram();
		glAttachShader(m_Program, m_VertexShader);
		glAttachShader(m_Program, m_FragmentShader);
		glLinkProgram(m_Program);

		int  success;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);

		if (!success)
		{
			int logLength = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &logLength);

			char* infoLog = new char[logLength + 1];

			glGetProgramInfoLog(m_Program, logLength, nullptr, infoLog);
			printf("ERROR::SHADER::PROGRAM::LINK_FAILED:\n%s", infoLog);
			assert(false && "Unable to link shader program, check console");

			delete[] infoLog;
		}
	}

	uint32_t Shader::GlShaderStageFromStage(Stage stage)
	{
		switch (stage)
		{
			case GL::Shader::Stage::Vertex: return GL_VERTEX_SHADER;
			case GL::Shader::Stage::Fragment: return GL_FRAGMENT_SHADER;
		}
		assert(false && "Forgot to specify Shader::GlShaderStageFromStage Return Value");
	}
}

std::string ReadShaderFile(const char* filepath)
{
	std::ifstream file(filepath);
	assert(file.is_open() && "Unable to open file");

	std::ostringstream sstr;
	sstr << file.rdbuf();

	file.close();

	return sstr.str();
}
