
#include <algorithm>

#include "Graphics/Components/Object.h"

#include "Graphics/Components/Camera/Camera.h"

namespace finitycore::Core::Graphics::Components {
	Object::Object(int64_t object_id, const std::string& object_name, const std::string& object_tag, bool& is_playing) 
		: m_objectID(object_id), 
		m_name(object_name), 
		m_tag(object_tag), 
		m_playing(is_playing), 
		transform(AddComponent<Components::Transform>()) 
	{
		CreatedEvent.Invoke(*this);
	}

	Object::~Object() {
		if (!m_sleeping) {
			if (IsActive()) OnDisable();
			if (m_awaked && m_started) OnDestroy();
		}

		DestroyedEvent.Invoke(*this);

		std::vector<Object*> toDetach = m_children;

		for (auto child : toDetach) child->DetachFromParent();
		toDetach.clear();

		DetachFromParent();

		std::for_each(m_components.begin(), m_components.end(), [&](std::shared_ptr<Components::Component> p_component) { ComponentRemovedEvent.Invoke(*p_component); });

		std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto& p_behaviour) { 
			BehaviourRemovedEvent.Invoke(std::ref(p_behaviour.second); });

		std::for_each(m_children.begin(), m_children.end(), [](Object* p_obj) { delete p_obj; });
	}

	const std::string& Object::GetObjectName() const
	{
		return m_name;
	}

	const std::string& Object::GetObjectTag() const
	{
		return m_tag;
	}

	void Object::SetObjectName(std::string& obj_name) { m_name = obj_name; }

	void Object::SetObjectTag(std::string& obj_tag) { m_tag = obj_tag; }

	void Object::SetActive(bool is_active) {
		if (is_active != m_active) {
			RecursiveWasActiveUpdate();
			m_active = is_active;
			RecursiveActiveUpdate();
		}
	}

	bool Object::IsSelfActive() const { return m_active; }

	bool Object::IsActive() const { return false; }

	void Object::SetObjectID(int64_t obj_id) { m_objectID = obj_id; }

	int64_t Object::GetObjectID() const { return m_objectID; }

	void Object::SetParentObject(Object& parent_obj) {
		DetachFromParent();

		m_parentObj = &parent_obj;
		m_parentObjID = parent_obj.m_objectID;

		transform.SetParent(parent_obj.transform);

		// Store the object in the parent children list
		parent_obj.m_children.push_back(this);

		ObjectAttachEvent.Invoke(*this, parent_obj);

	}
	void Object::DetachFromParent() {
		DetachEvent.Invoke(*this);

		if (m_parentObj) {
			m_parentObj->m_children.erase(std::remove_if(m_parentObj->m_children.begin(), m_parentObj->m_children.end(), [this](Object* p_obj) {
				return p_obj == this;
				}));
		}

		m_parentObj = nullptr;
		m_parentObjID = 0;

		transform.RemoveParent();
	}

	bool Object::HasParentObject() const { return m_parentObj; }

	Object* Object::GetParentObject() const { return m_parentObj; }

	int64_t Object::GetParentObjectID() const { return m_parentObjID; }

	std::vector<Object*>& Object::GetChildObjects()
	{
		// TODO: insert return statement here
	}
	void Object::MarkForDestructionGC()
	{
	}
	bool Object::IsAlive() const
	{
		return false;
	}
	void Object::SetIsSleep(bool is_sleeping)
	{
	}
	bool Object::RemoveComponent(Components::Component& component)
	{
		return false;
	}
	Components::Behaviour& Object::AddBehaviour(const std::string& name)
	{
		// TODO: insert return statement here
	}
	void Object::RecursiveActiveUpdate()
	{
	}
	void Object::RecursiveWasActiveUpdate()
	{
	}
}