#pragma once

#include "Engine/Renderer/Image2D.hpp"

//std
#include <cstdint>

namespace GL
{
	class Texture2D
	{
	public:
		inline static constexpr const uint32_t Max = 16;

	public:
		Texture2D(const Image2D& image);
		virtual ~Texture2D();

		Texture2D(const Texture2D& other) = delete;
		Texture2D& operator==(const Texture2D& other) = delete;

		inline uint32_t GetId() const { return m_Id; }

		void Bind(uint32_t slot);

	private:
		uint32_t m_Id;

	private:
		void CreateObject(const Image2D& image);
		void ParameterizeTexture() const;
		void SubImage(const Image2D& image) const;
	};
}
