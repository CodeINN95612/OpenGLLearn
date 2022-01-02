#include "Window.hpp"

#include "Engine/Events/Event.hpp"
#include "Engine/Events/KeyboardEvent.hpp"
#include "Engine/Events/MouseEvent.hpp"
#include "Engine/Events/WindowEvent.hpp"

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

		glfwSetWindowSizeCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, int width, int height)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				WindowResizeEvent::Type type = WindowResizeEvent::Type::Resize;

				int maximized = glfwGetWindowAttrib(pGLFWwindow, GLFW_MAXIMIZED);
				int minimized = height == 0;

				if(maximized == GLFW_TRUE)
					type = WindowResizeEvent::Type::Maximize;
				else if (minimized)
					type = WindowResizeEvent::Type::Minimize;

				pWindow->OnResize(width, height);

				WindowResizeEvent e(width, height, type);

				pWindow->GetEventFn()(e);
			}
		);

		glfwSetWindowMaximizeCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, int maximized)
			{
				if (maximized)
				{
					Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);
					WindowResizeEvent e(UINT32_MAX, UINT32_MAX, WindowResizeEvent::Type::Maximize);
					pWindow->GetEventFn()(e);
				}
			}
		);

		glfwSetWindowPosCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, int xPos, int yPos)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				WindowMoveEvent e(xPos, yPos);
				pWindow->GetEventFn()(e);
			}
		);

		glfwSetWindowCloseCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				WindowCloseEvent e;
				pWindow->GetEventFn()(e);
			}
		);

		glfwSetKeyCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, int key, int scancode, int action, int mods)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyboardKeyPressEvent e(key, false);
						pWindow->GetEventFn()(e);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyboardKeyReleaseEvent e(key);
						pWindow->GetEventFn()(e);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyboardKeyPressEvent e(key, true);
						pWindow->GetEventFn()(e);
						break;
					}
				}
				//assert(false && "Enum failure");
			}
		);

		glfwSetMouseButtonCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, int button, int action, int mods)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressEvent e(button);
						pWindow->GetEventFn()(e);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonReleaseEvent e(button);
						pWindow->GetEventFn()(e);
						break;
					}
				}
			}
		);

		glfwSetScrollCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, double xoffset, double yoffset)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				MouseScrollEvent e((float)xoffset, (float)yoffset);
				pWindow->GetEventFn()(e);
			}
		);

		glfwSetCursorPosCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, double xpos, double ypos)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				MouseMoveEvent e((uint32_t)xpos, (uint32_t)ypos);
				pWindow->GetEventFn()(e);
			}
		);

		glfwSetCharCallback((GLFWwindow*)m_pGLFWwindow, [](GLFWwindow* pGLFWwindow, unsigned int keyCode)
			{
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGLFWwindow);

				KeyboardCharEvent e(keyCode);
				pWindow->GetEventFn()(e);
			}
		);

		//glViewport(0, 0, m_Width, m_Height);
		glfwSwapInterval(1);
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_pGLFWwindow);
		glfwTerminate();
	}

	void Window::OnResize(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
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

	void Window::SetEventFunction(const EventFn& eventfn)
	{
		m_EventFunction = eventfn;
	}
}