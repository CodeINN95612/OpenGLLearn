#include "VertexBuffer.hpp"

//GL
#include <glad/glad.h>

//std
#include <assert.h>

namespace GL
{
	VertexBuffer::VertexBuffer(Type* attribLayout, uint32_t attribCount, void* data, uint32_t dataSize)
	{
		CreateObjects();
		SetData(data, dataSize);
		SpecifyAttributes(attribLayout, attribCount);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Vbo);
		glDeleteVertexArrays(1, &m_Vao);
	}

	void VertexBuffer::Bind()
	{
		glBindVertexArray(m_Vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	}

	void VertexBuffer::CreateObjects()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		glCreateBuffers(1, &m_Vbo);
	}

	void VertexBuffer::SetData(void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SpecifyAttributes(Type* attribLayout, uint32_t attribCount)
	{
		uint32_t stride = 0;
		for (uint32_t i = 0; i < attribCount; i++)
			stride += SizeFromType(attribLayout[i]);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < attribCount; i++)
		{
			Type type = attribLayout[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, CountFromType(type), GLTypeFromType(type), 
				GL_FALSE, stride, (void*)offset);
			offset += SizeFromType(attribLayout[i]);
		}		
	}

	uint32_t VertexBuffer::CountFromType(Type type)
	{
		switch (type)
		{
			case GL::VertexBuffer::Type::Float:
			case GL::VertexBuffer::Type::Int:
				return 1;

			case GL::VertexBuffer::Type::Float2:
			case GL::VertexBuffer::Type::Int2:
				return 2;

			case GL::VertexBuffer::Type::Float3:
			case GL::VertexBuffer::Type::Int3:
				return 3;

			case GL::VertexBuffer::Type::Float4:
			case GL::VertexBuffer::Type::Int4:
				return 4;
		}
		assert(false && "Forgot to specify VertexBuffer::CountFromType Return Value");
		return 0;
	}

	uint32_t VertexBuffer::SizeFromType(Type type)
	{
		switch (type)
		{
			case GL::VertexBuffer::Type::Float:  return 1 * sizeof(float);
			case GL::VertexBuffer::Type::Float2: return 2 * sizeof(float);
			case GL::VertexBuffer::Type::Float3: return 3 * sizeof(float);
			case GL::VertexBuffer::Type::Float4: return 4 * sizeof(float);

			case GL::VertexBuffer::Type::Int:  return 1 * sizeof(int);
			case GL::VertexBuffer::Type::Int2: return 2 * sizeof(float);
			case GL::VertexBuffer::Type::Int3: return 3 * sizeof(float);
			case GL::VertexBuffer::Type::Int4: return 4 * sizeof(float);
		}
		assert(false && "Forgot to specify VertexBuffer::SizeFromType Return Value");
		return 0;
	}

	uint32_t VertexBuffer::GLTypeFromType(Type type)
	{
		switch (type)
		{
			case GL::VertexBuffer::Type::Float:
			case GL::VertexBuffer::Type::Float2:
			case GL::VertexBuffer::Type::Float3:
			case GL::VertexBuffer::Type::Float4:
				return GL_FLOAT;

			case GL::VertexBuffer::Type::Int:
			case GL::VertexBuffer::Type::Int2:
			case GL::VertexBuffer::Type::Int3:
			case GL::VertexBuffer::Type::Int4:
				return GL_INT;
		}

		assert(false && "Forgot to specify VertexBuffer::GLTypeFromType Return Value");
		return 0;
	}
}