#pragma once
#include "Window.hpp"

namespace GL
{
	class Input
	{
	public:
		Input() = delete;
		virtual ~Input() = default;
		Input(const Input & other) = delete;
		Input& operator==(const Input & other) = delete;

		static void Initialize(Window& window);
		static void Terminate();

		static bool IsKeyPressed(int glfwKey);

	};
}
