#ifndef GEWI_CORE_UI
#define GEWI_CORE_UI

#include "../layout/ui-container.hpp"
#include "ui-object.hpp"

namespace gewi {
    class UI {
    private:
        UIContainer *root;
    public:
        UI();
        ~UI();
        void render();
        void add_ui_object(UIObject *obj);
    };
}
#endif