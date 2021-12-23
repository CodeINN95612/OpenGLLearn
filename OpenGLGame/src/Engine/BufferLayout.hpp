#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

//std
#include <memory>

namespace GL
{
	class BufferLayout
	{
	public:
		enum class VertexAttribType
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
		BufferLayout();
		virtual ~BufferLayout();

		BufferLayout(const BufferLayout& other) = delete;
		BufferLayout& operator==(const BufferLayout& other) = delete;

		void CreateVertexBuffer(void* data, uint32_t dataSize);
		void CreateIndexBuffer(void* data, uint32_t dataSize);
		void SetVertexAttributeTypes(VertexAttribType* vertexAttributes, uint32_t vertexAttributesCount);

		void Bind();
		void Unbind();
		void Draw(uint32_t vertexCount);

	private:
		uint32_t m_Vao;
		std::unique_ptr<VertexBuffer> m_pVertexBuffer;
		std::unique_ptr<IndexBuffer> m_pIndexBuffer;
		bool m_Specified = false;

	private:
		void SpecifyAttributes(VertexAttribType* attribLayout, uint32_t attribCount);

		static uint32_t CountFromType(VertexAttribType type);
		static uint32_t SizeFromType(VertexAttribType type);
		static uint32_t GLTypeFromType(VertexAttribType type);
	};
}
