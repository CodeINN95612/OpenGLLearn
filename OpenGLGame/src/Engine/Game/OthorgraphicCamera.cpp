#include "OthorgraphicCamera.hpp"

//glm
#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	OthorgraphicCamera::OthorgraphicCamera(uint32_t width, uint32_t height, glm::vec3 position)
	{
		UpdateViewProjectionMatrices(width, height);
	}

	void OthorgraphicCamera::OnUpdate()
	{
	}

	void OthorgraphicCamera::OnResize(uint32_t width, uint32_t height)
	{
		UpdateProjectionMatrix(width, height);
	}

	glm::mat4 OthorgraphicCamera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void OthorgraphicCamera::UpdateViewMatrix()
	{
	}

	void OthorgraphicCamera::UpdateProjectionMatrix(uint32_t width, uint32_t height)
	{
		m_ProjectionMatrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -(width / 2.0f), width / 2.0f);
	}

	void OthorgraphicCamera::UpdateViewProjectionMatrices(uint32_t width, uint32_t height)
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix(width, height);
	}
}