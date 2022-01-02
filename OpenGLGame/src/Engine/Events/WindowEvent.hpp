#pragma once

#include "Engine/Events/Event.hpp"

namespace GL
{
	class WindowResizeEvent : public Event
	{
	public:
		enum class Type
		{
			Resize,
			Minimize,
			Maximize,
		};

	public:
		WindowResizeEvent(uint32_t width, uint32_t height, Type type) :
			m_Width(width), m_Height(height), m_Type(type) {};
		virtual ~WindowResizeEvent() = default;

		inline static Category GetStaticCategory() { return Category::WindowResize; }
		virtual Category GetCategory() const override { return Category::WindowResize; }
		
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
		inline Type GetType() const { return m_Type; }

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		Type m_Type;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int32_t x, int32_t y) :
			m_X(x), m_Y(y) {}
		virtual ~WindowMoveEvent() = default;

		inline static Category GetStaticCategory() { return Category::WindowMove; }
		virtual Category GetCategory() const override { return Category::WindowMove; }

		inline int32_t GetPosX() const { return m_X; }
		inline int32_t GetPosY() const { return m_Y; }

	private:
		int32_t m_X, m_Y;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		virtual ~WindowCloseEvent() = default;

		inline static Category GetStaticCategory() { return Category::WindowClose; }
		virtual Category GetCategory() const override { return Category::WindowClose; }
	};
}
