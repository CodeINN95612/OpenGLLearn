#pragma once

#include "Engine/Core/Window.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/BufferLayout.hpp"

//std
#include <cstdint>
#include <memory>

//DEFINES

// If you're going to render widgets to the same
// UI from different source files, you can avoid
// ID collisions by defining IMGUI_SRC_ID before
// this define block:
#ifdef IMGUI_SRC_ID
#define GEN_ID ((IMGUI_SRC_ID) + (__LINE__))
#else
#define GEN_ID (__LINE__)
#endif

namespace GL::GUI
{
	class GuiRenderer
	{
		using GuiId = int64_t;
		using GuiColor = glm::vec4;

	public:
		GuiRenderer(uint32_t width, uint32_t height);
		virtual ~GuiRenderer() = default;

		GuiRenderer(const GuiRenderer& other) = delete;
		GuiRenderer& operator==(const GuiRenderer& other) = delete;

		void Begin(uint32_t width, uint32_t height); //TODO: move width and height to events
		void End();

		void WindowBegin(GuiId id, uint32_t x, uint32_t y);
		void WindowEnd();

		bool Button(GuiId id, uint32_t w, uint32_t h, uint32_t x = 0, uint32_t y = 0);

		//Style
		void SetMargin(uint32_t margin);
		void SetMargin(uint32_t marginL, uint32_t marginR, uint32_t marginT, uint32_t marginB);

	private:
		struct State
		{
			inline static uint32_t s_wndHeaderH = 15;

			uint32_t mouseX, mouseY;
			bool mousePressed;

			GuiId wndId = -1;
			uint32_t wndW, wndH, wndX, wndY;
			uint32_t wndXLayer = 0, wndYLayer = 0;

			GuiId hoveredId = -1;

			//Style
			uint32_t marginL = 0;
			uint32_t marginR = 0;
			uint32_t marginB = 0;
			uint32_t marginT = 0;
		};

		struct Data
		{
			bool begun;
			uint32_t width, height;
			std::unique_ptr<Shader> shader;
			std::unique_ptr<BufferLayout> bufferLayout;
		};

	private:
		State m_State{};
		Data m_Data{};

	private:
		void RenderRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, GuiColor color, float zLayer);

		void SetWndDimensions(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	};
}
