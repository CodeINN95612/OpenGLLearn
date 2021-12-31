#pragma once

//std
#include <cstdint>

namespace GL
{
	class Image2D
	{
	public:
		enum class Channel : uint8_t
		{
			R = 1,
			RG = 2,
			RGB = 3,
			RGBA = 4
		};

	public:
		Image2D(const char* filepath);
		Image2D(uint32_t width, uint32_t height, Channel channel = Channel::RGBA);
		Image2D(uint32_t width, uint32_t height, const void* buffer, uint32_t size, Channel channel = Channel::RGBA);
		virtual ~Image2D();

		Image2D(const Image2D& other) = delete;
		Image2D& operator==(const Image2D& other) = delete;

		void SetBuffer(const void* buffer, uint32_t size);
		inline const uint8_t* GetBuffer() const { return m_Buffer; }

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
		inline Channel GetChannel() const { return m_Channel; }

		uint32_t GetGLInternalFormat() const;
		uint32_t GetGLFormat() const;

	private:
		uint8_t* m_Buffer = nullptr;
		Channel m_Channel;
		uint32_t m_Width, m_Height;
		bool m_FromFile;
	};
}
