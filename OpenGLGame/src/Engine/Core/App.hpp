#pragma once

#include "Engine/Core/Window.hpp"
#include "Engine/Events/Event.hpp"

//std
#include <memory>

namespace GL
{
	class App
	{
	public:
		App(const char* name, uint32_t width, uint32_t height);
		virtual ~App();

		App(const App& other) = delete;
		App& operator==(const App& other) = delete;

		void Run();
		
		virtual void OnStart() = 0;
		virtual void OnUpdate(float deltatime) = 0;
		virtual void OnGui() = 0;
		virtual void OnEvent(Event& ev) = 0;
		virtual void OnEnd() = 0;

	protected:
		const char* m_Name;
		std::unique_ptr<Window> m_pWindow;

	private:
		void EventFn(Event& ev);
	};
}
