#pragma once

//glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace GL::ECS
{
	struct Transform2DComponent
	{
		glm::vec3 position{};
		glm::quat rotation{};
		glm::vec2 scale{ 1.0f, 1.0f };
	};
}
