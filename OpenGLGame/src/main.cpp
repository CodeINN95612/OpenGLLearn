#include <stdio.h>

//Mine
#include "Engine/Engine.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
    GL::Window window(WIDTH, HEIGHT);
    GL::Input::Initialize(window);

    GL::Renderer2D renderer;

    glm::vec3 pos{};
    while (!window.ShouldClose())
    {
        //Update
        pos.x += 1.0f;

        //Rendering
        GL::RendererCmd::Clear({ 0.2f, 0.3f, 0.3f, 1.0f });
        
        renderer.OnResize(window.GetWidth(), window.GetHeight());

        renderer.Begin();

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                renderer.Rect({ (i+ 0.05f) * 100.0f, (j+0.05f) * 100.0f, 0.0f }, { 90.0f, 90.0f });
            }
        }

        renderer.End();

        window.PollEvents();
        window.SwapBuffers();
    }

    GL::Input::Terminate();
	return 0;
}