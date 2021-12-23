#include "Window.hpp"

//GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std
#include <assert.h>

namespace GL
{
	Window::Window(uint32_t width, uint32_t height, const char* name) :
		m_Width(width), m_Height(height), m_Name(name)
	{
		assert(glfwInit() == GLFW_TRUE && "Unable to initialize glfw");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_pGLFWwindow = glfwCreateWindow(m_Width, m_Height, m_Name, nullptr, nullptr);
		assert(m_pGLFWwindow && "Unable to create glfw window");

		glfwSetWindowUserPointer((GLFWwindow*)m_pGLFWwindow, this);

		glfwMakeContextCurrent((GLFWwindow*)m_pGLFWwindow);

		assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "Unable to initialize glad");

		glfwSetFramebufferSizeCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pWindow, int width, int height)
			{
				glViewport(0, 0, width, height);
			}
		);

		glViewport(0, 0, m_Width, m_Height);
		glfwSwapInterval(1);
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_pGLFWwindow);
		glfwTerminate();
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

	void Window::WaitEvents() const
	{
		glfwWaitEvents();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers((GLFWwindow*)m_pGLFWwindow);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose((GLFWwindow*)m_pGLFWwindow);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose((GLFWwindow*)m_pGLFWwindow, true);
	}
}