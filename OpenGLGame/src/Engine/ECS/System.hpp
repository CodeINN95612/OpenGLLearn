#pragma once

#include "EntityID.hpp"

//std
#include <set>

namespace GL::ECS
{
	class System
	{
	public:
		virtual ~System() = default;

		System(const System& other) = delete;
		System& operator==(const System& other) = delete;

		inline std::set<EntityID>& GetEntities() { return m_Entities; }
		inline const std::set<EntityID>& GetEntities() const { return m_Entities; }

	protected:
		std::set<EntityID> m_Entities{};
	};
}
