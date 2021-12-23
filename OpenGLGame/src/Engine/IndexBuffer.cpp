#include "IndexBuffer.hpp"

//GL
#include <glad/glad.h>

namespace GL
{
	IndexBuffer::IndexBuffer(void* data, uint32_t dataSize)
	{
		glGenBuffers(1, &m_Ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_Ibo);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
	}
}