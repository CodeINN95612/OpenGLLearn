#pragma once

#include "ComponentID.hpp"
#include "System.hpp"

//std
#include <unordered_map>
#include <memory>
#include <assert.h>

namespace GL::ECS
{
	class SystemManager
	{
	public:
		SystemManager() = default;
		virtual ~SystemManager() = default;

		SystemManager(const SystemManager& other) = delete;
		SystemManager& operator==(const SystemManager& other) = delete;

		template<typename T>
		std::shared_ptr<T> Register()
		{
			const char* typeName = typeid(T).name();

			assert(m_Systems.find(typeName) == m_Systems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			m_Systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(ComponentSignature signature)
		{
			const char* typeName = typeid(T).name();

			assert(m_Systems.find(typeName) != m_Systems.end() && "System used before registered.");

			m_Signatures.insert({ typeName, signature });
		}

		void OnEntityDestroyed(EntityID entity)
		{
			// Erase a destroyed entity from all system lists
			// mEntities is a set so no check needed
			for (auto const& pair : m_Systems)
			{
				auto const& system = pair.second;

				system->GetEntities().erase(entity);
			}
		}

		void OnEntitySignatureChanged(EntityID entity, ComponentSignature entitySignature)
		{
			// Notify each system that an entity's signature changed
			for (auto const& pair : m_Systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_Signatures[type];

				// Entity signature matches system signature - insert into set
				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->GetEntities().insert(entity);
				}
				// Entity signature does not match system signature - erase from set
				else
				{
					system->GetEntities().erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, ComponentSignature> m_Signatures{};

		std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};
	};
}
