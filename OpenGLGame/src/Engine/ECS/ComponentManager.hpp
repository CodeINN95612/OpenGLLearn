#pragma once

#include "ComponentID.hpp"
#include "ComponentArray.hpp"

//std
#include <memory>

namespace GL::ECS
{
	class ComponentManager
	{
	public:
		ComponentManager() = default;
		virtual ~ComponentManager() = default;

		ComponentManager(const ComponentManager& other) = delete;
		ComponentManager& operator==(const ComponentManager& other) = delete;

		template<typename T>
		void Register()
		{
			const char* typeName = typeid(T).name();

			assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering component type more than once.");

			// Add this component type to the component type map
			m_ComponentTypes.insert({ typeName, m_NextComponent++ });

			// Create a ComponentArray pointer and add it to the component arrays map
			m_ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
		}

		template<typename T>
		ComponentID GetID()
		{
			const char* typeName = typeid(T).name();

			assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

			// Return this component's type - used for creating signatures
			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void Add(EntityID entity, T component)
		{
			// Add a component to the array for an entity
			GetComponentArray<T>()->Insert(entity, component);
		}

		template<typename T>
		void Remove(EntityID entity)
		{
			// Remove a component from the array for an entity
			GetComponentArray<T>()->Remove(entity);
		}

		template<typename T>
		T& Get(EntityID entity)
		{
			// Get a reference to a component from the array for an entity
			return GetComponentArray<T>()->Get(entity);
		}

		void OnEntityDestroyed(EntityID entity)
		{
			// Notify each component array that an entity has been destroyed
			// If it has a component for that entity, it will remove it
			for (auto const& pair : m_ComponentArrays)
			{
				auto const& component = pair.second;

				component->OnEntityDestroyed(entity);
			}
		}

	private:

		std::unordered_map<const char*, ComponentID> m_ComponentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};

		ComponentID m_NextComponent{};

		// Convenience function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
		}
	};
}
