#include "Texture2D.hpp"

#include <glad/glad.h>
#include <assert.h>
#include "Libs/stb_image/stb_image.hpp"

namespace GL
{
	Texture2D::Texture2D(const Image2D& image)
	{
		CreateObject(image);
		ParameterizeTexture();
		SubImage(image);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_Id);
	}

	void Texture2D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_Id);
	}

	void Texture2D::CreateObject(const Image2D& image)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
		glTextureStorage2D(m_Id, 1, image.GetGLInternalFormat(), image.GetWidth(), image.GetHeight());
	}

	void Texture2D::ParameterizeTexture() const
	{
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture2D::SubImage(const Image2D& image) const
	{
		glTextureSubImage2D(m_Id, 0, 0, 0, image.GetWidth(), image.GetHeight(), image.GetGLFormat(), GL_UNSIGNED_BYTE, image.GetBuffer());
	}
}