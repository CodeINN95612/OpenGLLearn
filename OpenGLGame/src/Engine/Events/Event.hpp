#pragma once

//std
#include <cstdint>
#include <functional>

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
		bool Handled;

	public:
		Event() = default;
		virtual ~Event() = default;

		inline static Category GetStaticCategory() { return Category::None; }
		virtual Category GetCategory() const { return Category::None; }
	};

}

#define EVENT_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)
