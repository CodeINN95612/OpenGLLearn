#include "RendererCmd.hpp"

//gl
#include <glad/glad.h>

namespace GL
{
	void RendererCmd::DrawVertices(uint32_t count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RendererCmd::DrawElements(uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

	void RendererCmd::Clear(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererCmd::Viewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		glViewport(x, y, w, h);
	}

	void RendererCmd::SetPolygonMode(PolygonMode mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GlPolygonModeFromPolygonMode(mode));
	}

	uint32_t RendererCmd::GlPolygonModeFromPolygonMode(PolygonMode polyMode)
	{
		switch (polyMode)
		{
			case PolygonMode::Fill: return GL_FILL;
			case PolygonMode::Line: return GL_LINE;
			case PolygonMode::Dot: return GL_POINT;
		}
		assert(false && "Enum not set correctly");
	}
}