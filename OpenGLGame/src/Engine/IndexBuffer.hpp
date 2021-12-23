#pragma once

//std
#include <cstdint>

namespace GL
{
	class IndexBuffer
	{
	public:
		IndexBuffer(void* data, uint32_t dataSize);
		virtual ~IndexBuffer();

		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer& operator==(const IndexBuffer& other) = delete;

		inline uint32_t GetIbo() const { return m_Ibo; }

		void Bind();

	private:
		uint32_t m_Ibo;
	};
}
