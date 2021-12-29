#pragma once

//std
#include <cstdint>

//glm
#include <glm/glm.hpp>

namespace GL
{
	class RendererCmd
	{
	public:
		enum class PolygonMode : uint8_t
		{
			Fill,
			Line,
			Dot
		};

	public:
		static void DrawVertices(uint32_t count);
		static void DrawElements(uint32_t count);

		static void Clear(glm::vec4 color);
		static void Viewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
		static void SetPolygonMode(PolygonMode mode);

	private:
		static uint32_t GlPolygonModeFromPolygonMode(PolygonMode polyMode);
	};
}
