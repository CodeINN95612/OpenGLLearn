#pragma once

#include "EntityID.hpp"

//std
#include <assert.h>
#include <array>
#include <unordered_map>

namespace GL::ECS
{
	class IComponentArray
	{
		//virtual inheritance is avoidable by using an Event function which I can also implement
		//something like what I did on the "Window" class before
		//for now this should not cause a major problem so that is it for now

	public:
		IComponentArray() = default;
		virtual ~IComponentArray() = default;

		virtual void OnEntityDestroyed(EntityID entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray() = default;
		virtual ~ComponentArray() = default;

		ComponentArray(const ComponentArray& other) = delete;
		ComponentArray& operator==(const ComponentArray& other) = delete;

		void Insert(EntityID entity, T component)
		{
			assert(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end() && "Component added to same entity more than once.");

			// Put new entry at end and update the maps
			size_t newIndex = m_Size++;
			m_EntityToIndexMap[entity] = newIndex;
			m_IndexToEntityMap[newIndex] = entity;
			m_Components[newIndex] = component;
		}

		void Remove(EntityID entity)
		{
			assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Removing non-existent component.");

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
			size_t indexOfLastElement = --m_Size;
			m_Components[indexOfRemovedEntity] = m_Components[indexOfLastElement];

			// Update map to point to moved spot
			EntityID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
			m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_EntityToIndexMap.erase(entity);
			m_IndexToEntityMap.erase(indexOfLastElement);
		}


		T& Get(EntityID entity)
		{
			assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Retrieving non-existent component.");

			// Return a reference to the entity's component
			return m_Components[m_EntityToIndexMap[entity]];
		}

		void OnEntityDestroyed(EntityID entity) override
		{
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				Remove(entity);
			}
		}

	private:
		std::array<T, MaxEntities> m_Components{};

		//The next unordered maps help by keeping components packed, 
		//I just copied this part because didn't really understand what it does but I do unserstand why it is important
		//https://austinmorlan.com/posts/entity_component_system/
		std::unordered_map<EntityID, size_t> m_EntityToIndexMap{};
		std::unordered_map<size_t, EntityID> m_IndexToEntityMap{};

		// Total size of valid entries in the array. cannot get frm array because the might not be valid enymore
		size_t m_Size{};
	};
}
