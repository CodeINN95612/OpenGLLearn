#pragma once

//std
#include <cstdint>
#include <functional>

#define EVENT_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GL
{
	class Event
	{
	public:
		enum class Category
		{
			None,
			WindowResize, WindowMove, WindowClose,
			MouseMove, MouseButtonPress, MouseButtonRelease, MouseScroll,
			KeayboardKeyPress, KeyboardKeyRelease, KeyboardChar
		};
		
	public:
		bool Handled{false};

	public:
		Event() = default;
		virtual ~Event() = default;

		inline static Category GetStaticCategory() { return Category::None; }
		virtual Category GetCategory() const { return Category::None; }
	};

	class EventManager
	{
	public:
		EventManager(Event& e) : m_Event(e) {}
		virtual ~EventManager() = default;

		template <typename T, typename FN>
		bool Dispatch(FN dispatchFunction)
		{
			if (m_Event.GetCategory() == T::GetStaticCategory())
			{
				dispatchFunction(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}

