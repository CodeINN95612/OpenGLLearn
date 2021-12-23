#pragma once

//std
#include <cstdint>

namespace GL
{

	class VertexBuffer
	{
	public:
		VertexBuffer(void* data, uint32_t dataSize);
		virtual ~VertexBuffer();

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator==(const VertexBuffer& other) = delete;

		inline uint32_t GetVbo() const { return m_Vbo; }

		void Bind();

	private:
		uint32_t m_Vbo;
	};
}
