#include "BufferLayout.hpp"

//Gl
#include <glad/glad.h>

//std
#include <assert.h>

namespace GL
{
	BufferLayout::BufferLayout()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);
	}

	BufferLayout::~BufferLayout()
	{
		glDeleteVertexArrays(1, &m_Vao);
	}

	void BufferLayout::CreateVertexBuffer(void* data, uint32_t dataSize)
	{
		glBindVertexArray(m_Vao);
		m_pVertexBuffer = std::make_unique<VertexBuffer>(data, dataSize);
	}

	void BufferLayout::CreateIndexBuffer(void* data, uint32_t dataSize)
	{
		glBindVertexArray(m_Vao);
		m_pIndexBuffer = std::make_unique<IndexBuffer>(data, dataSize);
	}

	void BufferLayout::SetVertexAttributeTypes(VertexAttribType* vertexAttributes, uint32_t vertexAttributesCount)
	{
		assert(m_pVertexBuffer && "A call to BufferLayout::CreateVertexBuffer is needed before this method call");
		glBindVertexArray(m_Vao);
		SpecifyAttributes(vertexAttributes, vertexAttributesCount);
	}

	void BufferLayout::Bind()
	{
		glBindVertexArray(m_Vao);
	}

	void BufferLayout::Unbind()
	{
		glBindVertexArray(0);
	}

	void BufferLayout::SpecifyAttributes(VertexAttribType* attribLayout, uint32_t attribCount)
	{
		uint32_t stride = 0;
		for (uint32_t i = 0; i < attribCount; i++)
			stride += SizeFromType(attribLayout[i]);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < attribCount; i++)
		{
			VertexAttribType type = attribLayout[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, CountFromType(type), GLTypeFromType(type),
				GL_FALSE, stride, reinterpret_cast<void*>(offset));
			offset += SizeFromType(attribLayout[i]);
		}
		m_Specified = true;
	}

	uint32_t BufferLayout::CountFromType(VertexAttribType type)
	{
		switch (type)
		{
		case VertexAttribType::Float:
		case VertexAttribType::Int:
			return 1;

		case VertexAttribType::Float2:
		case VertexAttribType::Int2:
			return 2;

		case VertexAttribType::Float3:
		case VertexAttribType::Int3:
			return 3;

		case VertexAttribType::Float4:
		case VertexAttribType::Int4:
			return 4;
		}
		assert(false && "Forgot to specify BufferLayout::CountFromType Return Value");
		return 0;
	}

	uint32_t BufferLayout::SizeFromType(VertexAttribType type)
	{
		switch (type)
		{
		case VertexAttribType::Float:  return 1 * sizeof(float);
		case VertexAttribType::Float2: return 2 * sizeof(float);
		case VertexAttribType::Float3: return 3 * sizeof(float);
		case VertexAttribType::Float4: return 4 * sizeof(float);

		case VertexAttribType::Int:  return 1 * sizeof(int);
		case VertexAttribType::Int2: return 2 * sizeof(float);
		case VertexAttribType::Int3: return 3 * sizeof(float);
		case VertexAttribType::Int4: return 4 * sizeof(float);
		}
		assert(false && "Forgot to specify BufferLayout::SizeFromType Return Value");
		return 0;
	}

	uint32_t BufferLayout::GLTypeFromType(VertexAttribType type)
	{
		switch (type)
		{
		case VertexAttribType::Float:
		case VertexAttribType::Float2:
		case VertexAttribType::Float3:
		case VertexAttribType::Float4:
			return GL_FLOAT;

		case VertexAttribType::Int:
		case VertexAttribType::Int2:
		case VertexAttribType::Int3:
		case VertexAttribType::Int4:
			return GL_INT;
		}

		assert(false && "Forgot to specify BufferLayout::GLTypeFromType Return Value");
		return 0;
	}
}