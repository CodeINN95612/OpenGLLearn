#include "Renderer2D.hpp"

#include "Engine/Renderer/Color.hpp"

//GL
#include <glad/glad.h>

//GLM
#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	Renderer2D::Renderer2D(uint32_t width, uint32_t height)
	{
		InitRectPipeline();
		OnResize(width, height);
	}

	Renderer2D::~Renderer2D()
	{
	}

	void Renderer2D::OnResize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer2D::Begin(const glm::mat4& viewProjectionMatrix)
	{
		m_CurrentViewProjection = viewProjectionMatrix;
	}

	void Renderer2D::End()
	{
	}

	void Renderer2D::Rect(glm::vec3 position, glm::vec2 size)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, { size.x,  size.y, 1.0f });

		//glm::mat4 view(1.0f);

		//glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.1f, 1.1f);

		m_RectPipeline->Bind(0);
		m_RectPipeline->GetShader()->SetTexture("uTexture", 0);
		m_RectPipeline->GetShader()->SetUniform4f("uColor", Color::Vec::Black);
		m_RectPipeline->GetShader()->SetUniformMat4f("uMVP", m_CurrentViewProjection * model);

		RendererCmd::DrawElements(6);
	}

	void Renderer2D::InitRectPipeline()
	{
		std::shared_ptr<Shader> rectShader = std::make_shared<Shader>("./assets/shaders/Renderer2D/Rect.vert", "./assets/shaders/Renderer2D/Rect.frag");
		
		float rectVertices[] = {
			-0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f
		};

		uint32_t rectindices[] = {
			0, 1, 2,
			2, 3, 0
		};

		BufferLayout::VertexAttribType attribs[] = { 
			BufferLayout::VertexAttribType::Float2,
			BufferLayout::VertexAttribType::Float2
		};

		std::shared_ptr<BufferLayout> bufferLayout = std::make_shared<BufferLayout>();
		bufferLayout->CreateVertexBuffer(rectVertices, sizeof(rectVertices));
		bufferLayout->CreateIndexBuffer(rectindices, sizeof(rectindices));
		bufferLayout->SetVertexAttributeTypes(attribs, sizeof(attribs));

		m_RectPipeline = std::make_unique<GraphicsPipeline2D>(bufferLayout, rectShader);

		uint32_t white = Color::Hex::White;
		Image2D whiteImg(1, 1, &white, sizeof(white));

		std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(whiteImg);

		m_RectPipeline->SetTexture(texture);

	}
}