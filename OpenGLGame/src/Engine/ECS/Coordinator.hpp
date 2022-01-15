#pragma once

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

namespace GL::ECS
{
	class Coordinator
	{
	public:
		Coordinator()
		{
			m_ComponentManager = std::make_unique<ComponentManager>();
			m_EntityManager = std::make_unique<EntityManager>();
			m_SystemManager = std::make_unique<SystemManager>();
		};

		virtual ~Coordinator() = default;

		Coordinator(const Coordinator& other) = delete;
		Coordinator& operator==(const Coordinator& other) = delete;



		// Entity methods
		EntityID CreateEntity()
		{
			return m_EntityManager->CreateEntity();
		}

		void DestroyEntity(EntityID entity)
		{
			m_EntityManager->DestroyEntity(entity);

			m_ComponentManager->OnEntityDestroyed(entity);

			m_SystemManager->OnEntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->Register<T>();
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			m_ComponentManager->Add<T>(entity, component);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetID<T>(), true);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->OnEntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			m_ComponentManager->Remove<T>(entity);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetID<T>(), false);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->OnEntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return m_ComponentManager->Get<T>(entity);
		}

		template<typename T>
		ComponentID GetComponentID()
		{
			return m_ComponentManager->GetID<T>();
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_SystemManager->Register<T>();
		}

		template<typename T>
		void SetSystemSignature(ComponentSignature signature)
		{
			m_SystemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> m_ComponentManager;
		std::unique_ptr<EntityManager> m_EntityManager;
		std::unique_ptr<SystemManager> m_SystemManager;
	};
}
