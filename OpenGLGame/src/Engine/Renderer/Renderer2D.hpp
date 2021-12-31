#pragma once

#include "Engine/Renderer/GraphicsPipeline2D.hpp"
#include "Engine/Renderer/RendererCmd.hpp"

//std
#include <memory>
#include <cstdint>

namespace GL
{
	class Renderer2D
	{
	public:
		Renderer2D();
		virtual ~Renderer2D();

		Renderer2D(const Renderer2D& other) = delete;
		Renderer2D& operator==(const Renderer2D& other) = delete;

		void OnResize(uint32_t width, uint32_t height);

		void Begin();
		void End();

		void Rect(glm::vec3 position, glm::vec2 size);

	private:
		std::unique_ptr<GraphicsPipeline2D> m_RectPipeline;
		uint32_t m_Width, m_Height;

	private:
		void InitRectPipeline();
	};
}
