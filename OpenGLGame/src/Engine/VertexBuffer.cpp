#include "VertexBuffer.hpp"

//GL
#include <glad/glad.h>

//std
#include <assert.h>

namespace GL
{
	VertexBuffer::VertexBuffer(void* data, uint32_t dataSize)
	{
		glCreateBuffers(1, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Vbo);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	}

}