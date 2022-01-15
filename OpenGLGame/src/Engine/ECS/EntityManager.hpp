#pragma once

#include "EntityID.hpp"
#include "ComponentID.hpp"

//std
#include <queue>
#include <array>
#include <assert.h>

namespace GL::ECS
{
	class EntityManager
	{
	public:
		EntityManager()
		{
			for (EntityID entity = 0; entity < MaxEntities; ++entity)
				m_AvailableEntities.push(entity);
		}

		virtual ~EntityManager() = default;

		EntityManager(const EntityManager& other) = delete;
		EntityManager& operator==(const EntityManager& other) = delete;

		EntityID CreateEntity()
		{
			assert(m_CurrentEntityCount < MaxEntities && "Entity out of range");

			EntityID entity = m_AvailableEntities.front();
			m_AvailableEntities.pop();
			++m_CurrentEntityCount;

			return entity;
		}

		void DestroyEntity(EntityID entity)
		{
			assert(entity < MaxEntities && "Entity out of range.");

			m_Signatures[entity].reset();

			m_AvailableEntities.push(entity);
			--m_CurrentEntityCount;
		}

		void SetSignature(EntityID entity, ComponentSignature signature)
		{
			assert(entity < MaxEntities && "Entity out of range.");

			m_Signatures[entity] = signature;
		}

		ComponentSignature GetSignature(EntityID entity)
		{
			assert(entity < MaxEntities && "Entity out of range.");

			return m_Signatures[entity];
		}

	private:
		std::queue<EntityID> m_AvailableEntities{};
		std::array<ComponentSignature, MaxEntities> m_Signatures;

		EntityID m_CurrentEntityCount{};
	};
}
