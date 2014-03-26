#ifndef GEWI_CORE_UI
#define GEWI_CORE_UI

#include "../widgets/ui-container.hpp"
#include "../render/renderer.hpp"
#include "ui-object.hpp"

namespace gewi {
    class UI {
    private:
        UIContainer *root;
        Renderer *flat_shader;
    public:
        UI();
        ~UI();
        void render();
        void add_ui_object(UIObject *obj);
        void click(float x, float y);
    };
}
#endif