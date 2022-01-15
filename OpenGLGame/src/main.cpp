#include <stdio.h>

//Mine
#include "Engine/Engine.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

class Game final : public GL::App
{
public:
    Game() : GL::App("Game", WIDTH, HEIGHT) {}
    virtual ~Game() = default;

    virtual void OnStart() override 
    {
    }

    void OnResize(GL::WindowResizeEvent& ev)
    {
        m_Renderer.OnResize(m_pWindow->GetWidth(), m_pWindow->GetHeight());
        m_Camera.OnResize(m_pWindow->GetWidth(), m_pWindow->GetHeight());
    }

    virtual void OnUpdate(float deltatime) override 
    {
        m_Pos.x += 1.0f;
        m_BGColor.b = glm::sin(glm::radians<float>(FrameCount)) / 2.0f + 0.5f;
        //Rendering
        GL::RendererCmd::Clear(m_BGColor);

        m_Renderer.Begin(m_Camera.GetViewProjectionMatrix());

        for (uint32_t i = 0; i < m_pWindow->GetWidth() / 50; i++)
        {
            for (uint32_t j = 0; j < m_pWindow->GetHeight() / 50; j++)
            {
                m_Renderer.Rect({ (i + 0.5f) * 50.0f, (j + 0.5f) * 50.0f, 0.0f }, { 40.0f, 40.0f });
            }
        }

        m_Renderer.End();

        ++FrameCount;
    }
    
    virtual void OnGui() override {}

    virtual void OnEvent(GL::Event& ev) override
    {
        GL::EventManager manager(ev);
        manager.Dispatch<GL::WindowResizeEvent>(EVENT_BIND_FN(Game::OnResize));
    }

    virtual void OnEnd() override {}

private:
    GL::Renderer2D m_Renderer{ WIDTH, HEIGHT };
    GL::OthorgraphicCamera m_Camera{WIDTH, HEIGHT, {0.0f, 0.0f, 0.0f}};

    glm::vec3 m_Pos{};
    glm::vec4 m_BGColor{0.05f, 1.0f, 0.05f, 1.0f};
    uint64_t FrameCount = 0;

};

void OnEvent(GL::Event& ev)
{
    printf("Event Category: %i \n", (int)ev.GetCategory());
}

using namespace GL::ECS;

int main(int argc, char** argv)
{
    Game game;
    game.Run();

    Coordinator coord;
    coord.RegisterComponent<Transform2DComponent>();

    EntityID entity = coord.CreateEntity();
    coord.AddComponent(entity, Transform2DComponent{});

	return 0;
}