#pragma once

//std
#include <cstdint>

namespace GL
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const char* name = "OpenGL");
		virtual ~Window();

		Window(const Window& other) = delete;
		Window& operator==(const Window& other) = delete;
		
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void OnResize(int width, int height);

		inline void* GetGLFWWindowPtr() { return m_pGLFWwindow; }

		void PollEvents() const;
		void WaitEvents() const;

		void SwapBuffers() const;

		bool ShouldClose() const;
		void Close();

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		const char* m_Name;

		void* m_pGLFWwindow = nullptr;
	};
}
