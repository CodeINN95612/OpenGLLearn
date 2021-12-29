#include "GuiRenderer.hpp"

//std
#include <assert.h>

//gl
#include <glad/glad.h>

//glm
#include <glm/gtc/matrix_transform.hpp>

//defines
#define ZLAYER_0 0.0f
#define ZLAYER_1 0.1f

namespace GL::GUI
{
	GuiRenderer::GuiRenderer(uint32_t width, uint32_t height)
	{
		//Initialize Shader Data

		float vertices[] = {
			-0.0f,  1.0f,
			-0.0f, -0.0f,
			 1.0f, -0.0f,
			 1.0f,  1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		BufferLayout::VertexAttribType attribs[] = { BufferLayout::VertexAttribType::Float2 };

		m_Data.shader = std::make_unique<Shader>("./shaders/GUI/Gui.vert", "./shaders/GUI/Gui.frag");

		m_Data.bufferLayout = std::make_unique<BufferLayout>();
		m_Data.bufferLayout->CreateVertexBuffer(vertices, sizeof(vertices));
		m_Data.bufferLayout->CreateIndexBuffer(indices, sizeof(indices));
		m_Data.bufferLayout->SetVertexAttributeTypes(attribs, 1);
	}

	void GuiRenderer::Begin(uint32_t width, uint32_t height)
	{
		assert(!m_Data.begun && "GUI has already begun, call GuiRenderer::End first");
		m_Data.begun = true;
		if(m_Data.width != width)
			m_Data.width = width;
		if (m_Data.height != height)
			m_Data.height = height;

		m_State.wndXLayer = 0;
		m_State.wndYLayer = 0;

		//Other renderer stuff
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void GuiRenderer::End()
	{
		assert(m_Data.begun && "GUI has not begun, call GuiRenderer::Begin first");
		m_Data.begun = false;
	}

	void GuiRenderer::WindowBegin(GuiId id, uint32_t x, uint32_t y)
	{
		//Update
		m_State.wndId = id;
		m_State.wndX = x;
		m_State.wndY = y + State::s_wndHeaderH;
		m_State.wndW = 100;
		m_State.wndH = 30;
	}

	void GuiRenderer::WindowEnd()
	{
		//Render
		RenderRect(m_State.wndX, m_State.wndY - State::s_wndHeaderH, m_State.wndW, State::s_wndHeaderH, { 0.15f, 0.15f, 0.15f, 1.0f }, ZLAYER_0);
		RenderRect(m_State.wndX, m_State.wndY, m_State.wndW, m_State.wndH, { 0.1f, 0.1f, 0.1f, 1.0f }, ZLAYER_0);
		
		m_State.wndId = -1;
	}

	bool GuiRenderer::Button(GuiId id, uint32_t w, uint32_t h, uint32_t x, uint32_t y)
	{
		assert(m_State.wndId != -1);
		//Update
		SetWndDimensions(x, y, w, h);

		m_State.wndXLayer += m_State.marginL;
		uint32_t nx = m_State.wndX + x + m_State.wndXLayer;
		m_State.wndXLayer += w + m_State.marginR;

		m_State.wndYLayer += m_State.marginT;
		uint32_t ny = m_State.wndY + y + m_State.wndYLayer;
		m_State.wndYLayer += h + m_State.marginB;

		//Render
		RenderRect(nx, ny, w, h, {1.0f, 0.0f, 0.0f, 1.0f}, ZLAYER_1);

		//Action
		return false;
	}

	void GuiRenderer::SetMargin(uint32_t margin)
	{
		SetMargin(margin, margin, margin, margin);
	}

	void GuiRenderer::SetMargin(uint32_t marginL, uint32_t marginR, uint32_t marginT, uint32_t marginB)
	{
		m_State.marginL = marginL;
		m_State.marginR = marginR;
		m_State.marginB = marginB;
		m_State.marginT = marginT;
	}

	void GuiRenderer::RenderRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, GuiColor color, float z)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, { x, y, z });
		model = glm::scale(model, { w,  h, z });

		m_Data.shader->Bind();
		m_Data.shader->SetUniformMat4f("uModel", model);
		m_Data.shader->SetUniformMat4f("uView", glm::mat4(1.0f));
		m_Data.shader->SetUniformMat4f("uProjection", glm::ortho(0.0f, (float)m_Data.width, (float)m_Data.height, 0.0f, -1.0f, 1.0f));
		m_Data.shader->SetUniform4f("uColor", color);

		m_Data.bufferLayout->Bind();
		//m_Data.bufferLayout->Draw(6);
	}

	void GuiRenderer::SetWndDimensions(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		uint32_t nw = m_State.wndXLayer + x + w + m_State.marginL + m_State.marginR;
		if (nw > m_State.wndW)
			m_State.wndW = nw;

		uint32_t nh = m_State.wndYLayer + y + h + + m_State.marginT + m_State.marginB;
		if (nh > m_State.wndH)
			m_State.wndH = nh;
	}
}