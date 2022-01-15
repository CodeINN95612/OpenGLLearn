#include <stdio.h>

//Mine
#include "Engine/Engine.hpp"

//defines
#define WIDTH 800
#define HEIGHT 600

class Game final : public GL::App
{
public:
    Game() : GL::App("Game", 1240, 720) {}
    virtual ~Game() = default;

    virtual void OnStart() override 
    {
    }

    virtual void OnUpdate(float deltatime) override 
    {
        m_Pos.x += 1.0f;

        //Rendering
        GL::RendererCmd::Clear(GL::Color::Vec::Gray25);

        m_Renderer.OnResize(m_pWindow->GetWidth(), m_pWindow->GetHeight());

        m_Renderer.Begin();

        for (uint32_t i = 0; i < m_pWindow->GetWidth() / 50; i++)
        {
            for (uint32_t j = 0; j < m_pWindow->GetHeight() / 50; j++)
            {
                m_Renderer.Rect({ (i + 0.5f) * 50.0f, (j + 0.5f) * 50.0f, 0.0f }, { 40.0f, 40.0f });
            }
        }

        m_Renderer.End();
    }
    
    virtual void OnGui() override {}

    virtual void OnEvent(GL::Event& ev) override {}

    virtual void OnEnd() override {}

private:
    GL::Renderer2D m_Renderer;
    glm::vec3 m_Pos;

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