#pragma once

#include "Engine/Events/Event.hpp"

namespace GL
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(uint32_t x, uint32_t y) :
			m_X(x), m_Y(y) {};
		virtual ~MouseMoveEvent() = default;

		inline static Category GetStaticCategory() { return Category::MouseMove; }
		virtual Category GetCategory() const override { return Category::MouseMove; }

		inline uint32_t GetPosX() const { return m_X; }
		inline uint32_t GetPosY() const { return m_Y; }

	private:
		uint32_t m_X, m_Y;

	};

	class MouseButtonPressEvent : public Event
	{
	public:
		MouseButtonPressEvent(uint32_t buttonCode) :
			m_ButtonCode(buttonCode) {};
		virtual ~MouseButtonPressEvent() = default;

		inline static Category GetStaticCategory() { return Category::MouseButtonPress; }
		virtual Category GetCategory() const override { return Category::MouseButtonPress; }

		inline uint32_t GetButtonCode() const { return m_ButtonCode; }

	private:
		uint32_t m_ButtonCode;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		MouseButtonReleaseEvent(uint32_t buttonCode) :
			m_ButtonCode(buttonCode) {};
		virtual ~MouseButtonReleaseEvent() = default;

		inline static Category GetStaticCategory() { return Category::MouseButtonRelease; }
		virtual Category GetCategory() const override { return Category::MouseButtonRelease; }

		inline uint32_t GetButtonCode() const { return m_ButtonCode; }

	private:
		uint32_t m_ButtonCode;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset) :
			m_XOffset(xOffset), m_YOffset(yOffset) {};
		virtual ~MouseScrollEvent() = default;

		inline static Category GetStaticCategory() { return Category::MouseButtonRelease; }
		virtual Category GetCategory() const override { return Category::MouseButtonRelease; }

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

	private:
		float m_XOffset, m_YOffset;
	};
}
