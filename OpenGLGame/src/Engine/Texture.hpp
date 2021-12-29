#pragma once

#include <cstdint>

namespace GL
{
	class Texture
	{
	public:
		enum class Channel
		{
			RGB,
			RGBA,
			Default = RGB
		};
	public:
		Texture(const char* filePath, Channel channel = Channel::Default);
		virtual ~Texture();

		Texture(const Texture& other) = delete;
		Texture& operator==(const Texture& other) = delete;

		inline uint32_t GetId() const { return m_Id; }
		inline uint8_t GetBindId() const { return m_BindId; }

		void Bind();

		static void FlipOnLoad(bool value);

	private:
		uint32_t m_Id;
		uint8_t m_BindId;

	private:
		void CreateObject();
		void ParameterizeTexture();
		void ReadAndSubImage(const char* filePath, Channel channel);

		static uint32_t GLFormatFromChannel(Channel channel);
	};
}
