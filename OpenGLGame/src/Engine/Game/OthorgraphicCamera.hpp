#pragma once

#include "Engine/Game/Camera.hpp"

namespace GL
{
	class OthorgraphicCamera : public Camera
	{
	public:
		OthorgraphicCamera(uint32_t width, uint32_t height, glm::vec3 position);
		virtual ~OthorgraphicCamera() = default;

		OthorgraphicCamera(const OthorgraphicCamera& other) = delete;
		OthorgraphicCamera& operator==(const OthorgraphicCamera& other) = delete;

		virtual void OnUpdate() override;
		virtual void OnResize(uint32_t width, uint32_t height) override;
		virtual glm::mat4 GetViewProjectionMatrix() const override;

	private:
		glm::mat4 m_ViewMatrix{1.0f};
		glm::mat4 m_ProjectionMatrix{1.0f};

	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix(uint32_t width, uint32_t height);
		void UpdateViewProjectionMatrices(uint32_t width, uint32_t height);
	};
}
