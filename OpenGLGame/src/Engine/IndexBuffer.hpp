#pragma once

namespace GL
{
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer& operator==(const IndexBuffer& other) = delete;
	};
}
