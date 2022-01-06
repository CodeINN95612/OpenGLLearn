#include "Engine/Core/App.hpp"

#include "Engine/Core/Input.hpp"

namespace GL
{
	App::App(const char* name, uint32_t width, uint32_t height) :
		m_Name(name)
	{
		m_pWindow = std::make_unique<Window>(width, height, name);
		m_pWindow->SetEventFunction(EVENT_BIND_FN(App::EventFn));
		GL::Input::Initialize(m_pWindow);
	}

	App::~App()
	{
		GL::Input::Terminate();
	}

	void App::Run()
	{
		OnStart();

        while (!m_pWindow->ShouldClose())
        {
            //Update
			OnUpdate(0.0f);

			//GUi
			OnGui();

			m_pWindow->PollEvents();
			m_pWindow->SwapBuffers();
        }

		OnEnd();
	}

	void App::EventFn(Event& ev)
	{
		OnEvent(ev);
	}
}
