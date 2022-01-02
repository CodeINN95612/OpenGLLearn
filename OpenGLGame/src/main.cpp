#include <stdio.h>

//Mine
#include "Engine/Engine.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

void OnEvent(GL::Event& ev)
{
    printf("Event Category: %i \n", (int)ev.GetCategory());
}

int main(int argc, char** argv)
{
    GL::Window window(WIDTH, HEIGHT);
    window.SetEventFunction(EVENT_BIND_FN(OnEvent));

    GL::Input::Initialize(window);

    GL::Renderer2D renderer;

    glm::vec3 pos{};
    while (!window.ShouldClose())
    {
        //Update
        pos.x += 1.0f;

        //Rendering
        GL::RendererCmd::Clear(GL::Color::Vec::Gray25);
        
        renderer.OnResize(window.GetWidth(), window.GetHeight());

        renderer.Begin();

        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                renderer.Rect({ (i+ 0.5f) * 50.0f, (j+ 0.5f) * 50.0f, 0.0f }, { 40.0f, 40.0f });
            }
        }

        renderer.End();

        window.PollEvents();
        window.SwapBuffers();
    }

    GL::Input::Terminate();
	return 0;
}