#pragma once
#include "Engine/Core/Window.hpp"

namespace GL
{
	class Input
	{
	public:
		Input() = delete;
		virtual ~Input() = default;
		Input(const Input & other) = delete;
		Input& operator==(const Input & other) = delete;

		static void Initialize(std::unique_ptr<Window>& window);
		static void Terminate();

		static bool IsKeyPressed(int glfwKey);

	};
}
