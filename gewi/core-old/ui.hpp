#ifndef GEWI_CORE_UI
#define GEWI_CORE_UI

#include "../widgets/ui-container.hpp"
#include "../render/renderer.hpp"
#include "ui-object.hpp"

namespace gewi {
    class UI {
    private:
        UIContainer *root;
        Renderer *flat_shader, *texture_shader;
    public:
        UI();
        ~UI();
        void layout();
        void render();
        void add_ui_object(UIObject *obj);
        void click(float x, float y);
        void key_press(int key, int mods);
    };
}
#endif