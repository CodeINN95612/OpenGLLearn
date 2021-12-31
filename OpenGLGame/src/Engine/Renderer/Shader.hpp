#pragma once

#include "Engine/Renderer/Texture2D.hpp"

//std
#include <cstdint>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GL
{
	class Shader
	{
	public:
		Shader(const char* vertexSource, const char* fragmentSource, uint8_t setThisToZero);
		Shader(const char* vertexFilepath, const char* fragmentFilepath);
		virtual ~Shader();

		Shader(const Shader& other) = delete;
		Shader& operator==(const Shader& other) = delete;

		void Bind();
		inline uint32_t GetGLProgram() const { return m_Program; }

		void SetUniform4f(const char* name, const glm::vec4 value);
		void SetUniform3f(const char* name, const glm::vec3 value);

		void SetUniform1i(const char* name, int32_t value);

		void SetUniformMat4f(const char* name, const glm::mat4& matrix);

		void SetTexture(const char* name, const uint32_t textureBindSlot);

	private:
		enum class Stage
		{
			Vertex,
			Fragment
		};

	private:
		uint32_t m_VertexShader;
		uint32_t m_FragmentShader;
		uint32_t m_Program;

	private:
		void Init(const char* vertexSource, const char* fragmentSource);

		static uint32_t CreateShader(Stage stage, const char* source);
		void CreateProgram();

		static uint32_t GlShaderStageFromStage(Stage stage);
		uint32_t GetGLUniformPos(const char* name);
	};
}
