#pragma once

#include "Engine/Events/Event.hpp"

//std
#include <cstdint>

namespace GL
{
	class Window
	{
		using EventFn = std::function<void(Event&)>;
	public:
		Window(uint32_t width, uint32_t height, const char* name = "OpenGL");
		virtual ~Window();

		Window(const Window& other) = delete;
		Window& operator==(const Window& other) = delete;
		
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void OnResize(uint32_t width, uint32_t height);

		inline void* GetGLFWWindowPtr() { return m_pGLFWwindow; }

		void PollEvents() const;
		void WaitEvents() const;

		void SwapBuffers() const;

		bool ShouldClose() const;
		void Close();

		void SetEventFunction(const EventFn& eventfn);
		inline const EventFn& GetEventFn() const { return m_EventFunction; }

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		const char* m_Name;
		EventFn m_EventFunction;

		void* m_pGLFWwindow = nullptr;
	};
}
