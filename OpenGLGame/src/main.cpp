#include <stdio.h>

//GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std
#include <assert.h>

//Mine
#include "Engine/Window.hpp"
#include "Engine/Input.hpp"
#include "Engine/BufferLayout.hpp"
#include "Engine/Shader.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

static bool polygonMode = false;
static bool isPressed = false;
static glm::vec3 offset{0.0f};

void input(GL::Window& window)
{
    if (GL::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        window.Close();

    if (GL::Input::IsKeyPressed(GLFW_KEY_P))
    {
        glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);
        if(!isPressed)
            polygonMode = !polygonMode;
        isPressed = true;
    }
    else
        isPressed = false;

    if(GL::Input::IsKeyPressed(GLFW_KEY_RIGHT))
        offset.x += 0.01;
    if (GL::Input::IsKeyPressed(GLFW_KEY_LEFT))
        offset.x -= 0.01;
    if (GL::Input::IsKeyPressed(GLFW_KEY_UP))
        offset.y += 0.01;
    if (GL::Input::IsKeyPressed(GLFW_KEY_DOWN))
        offset.y -= 0.01;
}

int main(int argc, char** argv)
{
    GL::Window window(WIDTH, HEIGHT);
    GL::Input::Initialize(window);

    GL::Shader simpleShader("./shaders/SimpleShader.vert", "./shaders/SimpleShader.frag");

    float vertices[] = {
        -0.5f,  0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f 
    };

    uint32_t indices[] = {
        0u, 1u, 2u,
        2u, 3u, 0u
    };
    
    GL::BufferLayout::VertexAttribType verticesLayout[] = { 
        GL::BufferLayout::VertexAttribType::Float3
    };

    GL::BufferLayout bufferLayout;
    bufferLayout.CreateVertexBuffer(vertices, sizeof(vertices));
    bufferLayout.CreateIndexBuffer(indices, sizeof(indices));
    bufferLayout.SetVertexAttributeTypes(verticesLayout, sizeof(verticesLayout) / sizeof(verticesLayout[0]));

    while (!window.ShouldClose())
    {
        input(window);

        //Update
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        simpleShader.Bind();
        //simpleShader.SetUniform4f("uColor", { 0.0f, greenValue, 0.0f, 1.0f });
        simpleShader.SetUniform3f("uOffset", offset);

        bufferLayout.Bind();
        bufferLayout.Draw(6); // I dont like Draw there, it should be a renderer problem
        bufferLayout.Unbind();

        window.PollEvents();
        window.SwapBuffers();
    }

    GL::Input::Terminate();
	return 0;
}