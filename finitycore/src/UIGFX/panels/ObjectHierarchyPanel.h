#pragma once

#ifndef FINITY_GUI_OBJECTHIERARCHYPANEL_H
#define FINITY_GUI_OBJECTHIERARCHYPANEL_H

#include "../Panel.h"

namespace Finity { namespace GUI { namespace Panel {

    class ObjectHierarchyPanel : public finPanel {

    public:
        ObjectHierarchyPanel = default;
        ObjectHierarchyPanel(const Ref<Object>& object);
        void SetContext(const Ref<Object>& object);
        void OnGuiRender();

        Entity GetSelectedEntity() const;
        void SetSelectedEntity(Entity entity);

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

    private:
        Entity m_SelectedContext;
    };
}}}

#endif //FINITY_GUI_OBJECTHIERARCHYPANEL_H
