#pragma once
#include <vector>

#include "Graphics/Components/Camera/Camera.h"
#include "Graphics/Components/Light.h";

namespace finitycore::Core::Graphics::SceneSystem {

	class Scene : public serializer::ISerializable {
	public:
		struct FastAccessComponents {
			std::vector<Components::CModelRenderer*> modelRenderer;
			std::vector<Components::Camera*> cameras;
			std::vector<Components::Light*> lights;
		};
		
		// Constructor
		Scene();
		
		// Desctructor
		~Scene();
			
		// Play the scene
		void Play();

		// Return True if the scene is being played
		bool IsPlaying() const;

		// Udpate every object on call
		void Update(float p_deltaTime);

		// Set to update every objects every `p_deltaTime`
		void Fixedupdate(float p_deltaTime);
		
		// Update every objects delayed
		void DelayedUpdate(float p_deltaTime);
		
		// Create an actor with a default name and return a reference to it
		Components::Object& CreateObject();

		// Create an object and return a reference to it
		Components::Object& CreateObject(const std::string& obj_name, const std::string& obj_tag = "");

		// Destroy an object by reference
		bool DestroyObject(Components::Object& target_Obj);

		// Scene Garbage Collector
		void GC();

		// Return the object identified by the ID, or return nullptr or throw exception
		Components::Object* FindObjectByOID(int64_t obj_ID);

		// Return the first object identified by the `obj_name`, or return nullptr or throw exception
		Components::Object* FindObjectByName(const std::string& obj_name);

		// Return the first object identified by the `obj_tag`, or return nullptr or throw exception
		Components::Object* FindObjectByTag(const std::string& obj_tag);

		// Return every object identified by the `obj_name`
		std::vector<std::reference_wrapper<Components::Object>> FindObjectsByName(const std::string& obj_name);

		// Return every object identified by the `obj_tag`
		std::vector<std::reference_wrapper<Components::Object>> FindObjectsByTag(const std::string& obj_tag);

		// Callback on adding of component(can be object)
		void OnObjectAdded(Components::Object& object);
		// Callback on adding of component(can be object)
		void OnObjectRemoved(Components::Object& object);

		// Get a reference map of the objects
		std::vector<Components::Object*>& GetObjects();

		// Get the fast access components
		const FastAccessComponents& GetFastAccessComponents() const;

		// Serialize the Scene Object into an XML Document
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_root) override;
		// Deserialize the scene from the scene XML Document
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_root) override;

	private:
		int64_t m_avaiableID = 1;
		bool m_isPlaying = false;
		std::vector<Components::Object*> m_objects;

		FastAccessComponents m_fastAccessComponents;
	};
}