#include "Input.hpp"

//GL
#include <GLFW/glfw3.h>

//std
#include <assert.h>

namespace GL
{
	static GLFWwindow* pWindow = nullptr;

	void Input::Initialize(std::unique_ptr<Window>& window)
	{
		pWindow = (GLFWwindow*)window->GetGLFWWindowPtr();
	}

	void Input::Terminate()
	{
		pWindow = nullptr;
	}

	bool Input::IsKeyPressed(int glfwKey)
	{
		assert(pWindow && "Input has to be initialized first");
		return glfwGetKey(pWindow, glfwKey) == GLFW_PRESS;
	}
}