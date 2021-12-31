#include "GraphicsPipeline2D.hpp"

//std
#include <assert.h>

namespace GL
{
	GraphicsPipeline2D::GraphicsPipeline2D(std::shared_ptr<BufferLayout> layout, std::shared_ptr<Shader> shader) :
		m_Layout(layout), m_Shader(shader)
	{
	}

	void GraphicsPipeline2D::Bind()
	{
		assert(!(bool)m_Texture && "Texture must be bound with a unit");
		m_Layout->Bind();
		m_Shader->Bind();
	}

	void GraphicsPipeline2D::Bind(uint32_t textureUnit)
	{
		assert((bool)m_Texture && "Texture must be set to bind with a unit");
		m_Layout->Bind();
		m_Shader->Bind();
		m_Texture->Bind(textureUnit);
	}
}