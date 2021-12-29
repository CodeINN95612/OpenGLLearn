#include "Pipeline.hpp"

//std
#include <assert.h>

namespace GL
{
	Pipeline::Pipeline(std::shared_ptr<BufferLayout> layout, std::shared_ptr<Shader> shader) :
		m_Layout(layout), m_Shader(shader)
	{
	}

	void Pipeline::Bind()
	{
		m_Layout->Bind();
		m_Shader->Bind();
	}
}