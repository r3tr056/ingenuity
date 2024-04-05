#include "ObjectHierarchyPanel.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>

namespace Finity { namespace GUI { namespace Panel {
    ObjectHierarchyPanel::ObjectHierarchyPanel(const Ref<Object> &object) {
        SetContext(object);
    }

    void ObjectHierarchyPanel::onRender() {
        ImGui::Begin("Object Hierarchy");

        m_Context->m_Registry.each([&](auto entityID) {
            Enitity entity{ entityID, m_Context.get() };
            DrawEntityNode(entity);
        });

        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Create an Empty Object"))
                m_Context->CreateEmpty("Empty Object");
            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Properties")
    }

}}}