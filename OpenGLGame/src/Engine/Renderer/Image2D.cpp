#include "Image2D.hpp"

//libs
#include <Libs/stb_image/stb_image.hpp>
#include <glad/glad.h>

//std
#include <assert.h>
#include <string.h>

namespace GL
{
	Image2D::Image2D(const char* filepath) :
		m_FromFile(true)
	{
		int width, height, channels;
		//stbi_set_flip_vertically_on_load(true);

		m_Buffer = stbi_load(filepath, &width, &height, &channels, 0);
		assert(m_Buffer && "Unable to load image from filepath");

		m_Width = width;
		m_Height = height;

		m_Channel = (Channel)channels;
	}

	Image2D::Image2D(uint32_t width, uint32_t height, Channel channel) :
		m_Width(width), m_Height(height), m_Channel(channel), m_FromFile(false)
	{
		m_Buffer = new uint8_t[m_Width * m_Height * (int)m_Channel];
	}

	Image2D::Image2D(uint32_t width, uint32_t height, const void* buffer, uint32_t size, Channel channel) :
		m_Width(width), m_Height(height), m_Channel(channel), m_FromFile(false)
	{
		m_Buffer = new uint8_t[m_Width * m_Height * (int)m_Channel];
		SetBuffer(buffer, size);
	}

	Image2D::~Image2D()
	{
		if (m_FromFile)
			stbi_image_free(m_Buffer);
		else
			delete[] m_Buffer;
	}

	void Image2D::SetBuffer(const void* buffer, uint32_t size)
	{
		assert(!m_FromFile && "Buffer has already been loaded from file");
		assert(m_Width * m_Height * (int)m_Channel == size && "Incorrect size for Image");
		memcpy_s(m_Buffer, m_Width * m_Height * (int)m_Channel, buffer, size);
	}
	uint32_t Image2D::GetGLInternalFormat() const
	{
		switch (m_Channel)
		{
			case Channel::R: return GL_R8;
			case Channel::RG: return GL_RG8;
			case Channel::RGB: return GL_RGB8;
			case Channel::RGBA: return GL_RGBA8;
		}
		assert(false && "Enumeration error");
		return 0;
	}
	uint32_t Image2D::GetGLFormat() const
	{
		switch (m_Channel)
		{
			case Channel::R: return GL_RED;
			case Channel::RG: return GL_RG;
			case Channel::RGB: return GL_RGB;
			case Channel::RGBA: return GL_RGBA;
		}
		assert(false && "Enumeration error");
		return 0;
	}
}