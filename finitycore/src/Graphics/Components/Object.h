#pragma once

#include <unordered_map>
#include <memory>

#include "Graphics/Components/Component.h"
#include "Graphics/Components/Transform/Transform.h"
#include "Graphics/Components/Behaviour.h"

#include "Graphics/Components/Collision/Collision.h"

namespace finitycore::Core::Graphics::Components {

	class PhysicalObject {};

	class Object : public Component, public util::Serializable {
	public:
		Object(int64_t object_id, const std::string& object_name, const std::string& object_tag, bool& is_playing);

		virtual ~Object() override;

		const std::string& GetObjectName() const;

		const std::string& GetObjectTag() const;

		void SetObjectName(std::string& obj_name);

		void SetObjectTag(std::string& obj_tag);

		void SetActive(bool is_active);

		bool IsSelfActive() const;

		bool IsActive() const;

		void SetObjectID(int64_t obj_id);

		int64_t GetObjectID() const;

		void SetParentObject(Object& parent_obj);

		void DetachFromParent();

		bool HasParentObject() const;

		Object* GetParentObject() const;

		int64_t GetParentObjectID() const;

		std::vector<Object*>& GetChildObjects();

		void MarkForDestructionGC();

		bool IsAlive() const;

		void SetIsSleep(bool is_sleeping);

		virtual void OnAwake() = 0;

		virtual void OnStart() = 0;

		virtual void OnEnable() = 0;

		virtual void OnDisable() = 0;

		virtual void OnEnable() = 0;

		virtual void OnDestroy() = 0;

		virtual void OnUpdate(float deltaTime) = 0;

		virtual void OnFixedUpdate(float deltaTime) = 0;

		virtual void OnLateUpdate(float deltaTime) = 0;

		virtual void OnCollisionEnter(Components::PhysicalObject& otherObj) = 0;

		virtual void OnCollisionStay(Components::PhysicalObject& otherObj) = 0;

		virtual void OnCollisionExit(Components::PhysicalObject& otherObj) = 0;

		virtual void OnTriggerEnter(Components::PhysicalObject& otherObj) = 0;

		virtual void OnTriggerStay(Components::PhysicalObject& otherObj) = 0;

		virtual void OnTriggerExit(Components::PhysicalObject& otherObj) = 0;

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		bool RemoveComponent();

		bool RemoveComponent(Components::Component& component);

		template<typename T>
		T* GetComponent();

		std::vector<std::shared_ptr<Components::Component>>& GetComponents();

		Components::Behaviour& AddBehaviour(const std::string& name);

		bool RemoveBehaviour();

	private:
		Object(const Object& obj) = delete;

		void RecursiveActiveUpdate();
		void RecursiveWasActiveUpdate();

	public:
		// Somve events that are trigered when an action occur on the Object instance
		Eventing::Event<Components::Component&> ComponentAddedEvent;
		Eventing::Event<Components::Component&> ComponentRemovedEvent;

		Eventing::Event<Components::Behaviour&> BehaviourAddedEvent;
		Eventing::Event<Components::Behaviour&> BehaviourRemovedEvent;

		// Events triggered when action occur by object
		static Eventing::Event<Components::Object&> ObjectDestroyedEvent;
		static Eventing::Event<Components::Object&> ObjectCreatedEvent;
		static Eventing::Event<Components::Object&, Components::Object&> ObjectAttachEvent;
		static Eventing::Event<Components::Object&> ObjectDetachEvent;


		Components::Transform& transform;

	private:
		// Object properties
		std::string m_name;
		std::string m_tag;

		bool m_active = true;
		bool& m_playing;

		int64_t m_objectID;
		bool m_destroyed = false;
		bool m_sleeping = true;
		bool m_awaked = false;
		bool m_started = false;
		bool m_wasActive = false;

		// Object's Parent/Child System
		int64_t m_parentObjID = 0;
		Object* m_parentObj = nullptr;
		std::vector<Object*> m_children;

		// Object's components 
		std::vector<std::shared_ptr<Components::Component>> m_components;
		std::unordered_map<std::string, Components::Behaviour> m_behaviours;

	};
	template<typename T, typename ...Args>
	inline T& Object::AddComponent(Args && ...args)
	{
		// TODO: insert return statement here
	}
	template<typename T>
	inline bool Object::RemoveComponent()
	{
		return false;
	}
}