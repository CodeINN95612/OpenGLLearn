#pragma once

//glm
#include <glm/glm.hpp>

namespace GL::Color
{
	struct Vec
	{
		inline static constexpr const glm::vec4 Red{ 1.0f, 0.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Green{ 0.0f, 1.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Black{ 0.0f, 0.0f, 0.0f, 1.0f };
		inline static constexpr const glm::vec4 White{ 1.0f, 1.0f, 1.0f, 1.0f };
		inline static constexpr const glm::vec4 Gray25{ 0.75f, 0.75f, 0.75f, 1.0f };
		inline static constexpr const glm::vec4 Gray50{ 0.5f, 0.5f, 0.5f, 1.0f };
		inline static constexpr const glm::vec4 Gray75{ 0.25f, 0.25f, 0.25f, 1.0f };
	};

	struct Hex
	{
		inline static constexpr const uint32_t Red = 0xff0000ff;
		inline static constexpr const uint32_t Green = 0xff00ff00;
		inline static constexpr const uint32_t Blue = 0xffff0000;
		inline static constexpr const uint32_t Yellow = 0xff00ffff;
		inline static constexpr const uint32_t Magenta = 0xffff00ff;
		inline static constexpr const uint32_t Cyan = 0xffffff00;
		inline static constexpr const uint32_t Black = 0xff000000;
		inline static constexpr const uint32_t White = 0xffffffff;
		inline static constexpr const uint32_t Gray25 = 0xffbfbfbf;
		inline static constexpr const uint32_t Gray50 = 0xff7f7f7f;
		inline static constexpr const uint32_t Gray75 = 0xff444444;
	};
}
