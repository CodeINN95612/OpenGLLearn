#include <stdio.h>

//GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std
#include <assert.h>

//Mine
#include "Engine/Window.hpp"
#include "Engine/Input.hpp"
#include "Engine/VertexBuffer.hpp"
#include "Engine/Shader.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

void input(GL::Window& window)
{
    if (GL::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        window.Close();
}

int main(int argc, char** argv)
{
    GL::Window window(WIDTH, HEIGHT);
    GL::Input::Initialize(window);

    GL::Shader simpleShader("./shaders/SimpleShader.vert", "./shaders/SimpleShader.frag");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GL::VertexBuffer::Type verticesLayout[] = { 
        GL::VertexBuffer::Type::Float3, 
        GL::VertexBuffer::Type::Float3 
    };

    GL::VertexBuffer vertexBuffer(verticesLayout, sizeof(verticesLayout)/sizeof(verticesLayout[0]), vertices, sizeof(vertices));

    while (!window.ShouldClose())
    {
        input(window);

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        simpleShader.Bind();
        vertexBuffer.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.PollEvents();
        window.SwapBuffers();
    }

    GL::Input::Terminate();
	return 0;
}