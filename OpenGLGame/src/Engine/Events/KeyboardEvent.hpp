#pragma once

#include "Engine/Events/Event.hpp"

namespace GL
{
	class KeyboardKeyPressEvent : public Event
	{
	public:
		KeyboardKeyPressEvent(uint32_t keyCode, bool isRepeat) :
			m_KeyCode(keyCode), m_IsRepeat(isRepeat) {}
		virtual ~KeyboardKeyPressEvent() = default;

		inline static Category GetStaticCategory() { return Category::KeayboardKeyPress; }
		virtual Category GetCategory() const override { return Category::KeayboardKeyPress; }

		inline uint32_t GetKeyCode() const { return m_KeyCode; }
		inline bool IsRepeat() const { return m_IsRepeat; }

	private:
		uint32_t m_KeyCode;
		bool m_IsRepeat;

	};

	class KeyboardKeyReleaseEvent : public Event
	{
	public:
		KeyboardKeyReleaseEvent(uint32_t keyCode) :
			m_KeyCode(keyCode) {}
		virtual ~KeyboardKeyReleaseEvent() = default;

		inline static Category GetStaticCategory() { return Category::KeyboardKeyRelease; }
		virtual Category GetCategory() const override { return Category::KeyboardKeyRelease; }

		inline uint32_t GetKeyCode() const { return m_KeyCode; }

	private:
		uint32_t m_KeyCode;

	};

	class KeyboardCharEvent : public Event
	{
	public:
		KeyboardCharEvent(char character) :
			m_Character(character) {}
		virtual ~KeyboardCharEvent() = default;

		inline static Category GetStaticCategory() { return Category::KeyboardChar; }
		virtual Category GetCategory() const override { return Category::KeyboardChar; }

		inline char GetCharacter() const { return m_Character; }

	private:
		char m_Character;

	};
}
