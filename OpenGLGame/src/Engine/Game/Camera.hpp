#pragma once

//std
#include <cstdint>

//glm
#include <glm/glm.hpp>

namespace GL
{
	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual void OnUpdate() = 0;
		virtual void OnResize(uint32_t width, uint32_t height) = 0;
		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
	};
}
