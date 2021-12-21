#pragma once
#include <cstdint>

namespace GL
{

	class VertexBuffer
	{
	public:
		enum class Type
		{
			Float,
			Float2,
			Float3,
			Float4,

			Int,
			Int2,
			Int3,
			Int4
		};
	public:
		VertexBuffer(Type* attribLayout, uint32_t attribCount, void* data, uint32_t dataSize);
		virtual ~VertexBuffer();

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator==(const VertexBuffer& other) = delete;

		inline uint32_t GetVbo() const { return m_Vbo; }
		inline uint32_t GetVao() const { return m_Vao; }

		void Bind();

	private:
		uint32_t m_Vbo;
		uint32_t m_Vao;

	private:
		void CreateObjects();
		void SetData(void* data, uint32_t size);
		void SpecifyAttributes(Type* attribLayout, uint32_t attribCount);

		static uint32_t CountFromType(Type type);
		static uint32_t SizeFromType(Type type);
		static uint32_t GLTypeFromType(Type type);
	};
}
