#include <stdio.h>

//GL
#include <GLFW/glfw3.h>

//std
#include <assert.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Mine
#include "Engine/Window.hpp"
#include "Engine/Input.hpp"
#include "Engine/BufferLayout.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Renderer/RendererCmd.hpp"
#include "Engine/Renderer/Renderer2D.hpp"

//GUI
#include "Engine/GUI/GuiRenderer.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

void input(GL::Window& window)
{

}

int main(int argc, char** argv)
{
    GL::Window window(WIDTH, HEIGHT);
    GL::Input::Initialize(window);

    GL::Renderer2D renderer;

    glm::vec3 pos{};
    while (!window.ShouldClose())
    {
        input(window);

        //Update
        pos.x += 1.0f;

        //Rendering
        GL::RendererCmd::Clear({ 0.2f, 0.3f, 0.3f, 1.0f });
        
        renderer.OnResize(window.GetWidth(), window.GetHeight());

        renderer.Begin();

        renderer.Rect(pos, { 100.0f, 100.0f });

        renderer.End();

        window.PollEvents();
        window.SwapBuffers();
    }

    GL::Input::Terminate();
	return 0;
}