#include "Texture.hpp"

#include <glad/glad.h>
#include <assert.h>
#include "Libs/stb_image/stb_image.hpp"

namespace GL
{
	static uint8_t s_BindId = 0;

	Texture::Texture(const char* filePath, Channel channel)
	{
		CreateObject();
		ParameterizeTexture();
		ReadAndSubImage(filePath, channel);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_Id);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + m_BindId);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void Texture::FlipOnLoad(bool value)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	void Texture::CreateObject()
	{
		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		m_BindId = s_BindId;
		s_BindId++;
		assert(s_BindId <= 16 && "Can't create more than 16 textures for now");
	}

	void Texture::ParameterizeTexture()
	{
		//Texture already bound
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Texture::ReadAndSubImage(const char* filePath, Channel channel)
	{
		int width, height, nrChannels;
		unsigned char* data1 = stbi_load(filePath, &width, &height, &nrChannels, 0);
		assert(data1 && "Unable to read image");

		//Texture already bound
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GLFormatFromChannel(channel), GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data1);
	}
	uint32_t Texture::GLFormatFromChannel(Channel channel)
	{
		switch (channel)
		{
			case Channel::RGB: return GL_RGB;
			case Channel::RGBA: return GL_RGBA;
		}
		assert(false, "Enum not configured");
	}
}