#include "ui.hpp"

#include "../interaction/clickable.hpp"

namespace gewi {
    UI::UI() {
        root = new UIContainer();
        root->set_dim(1, 1);
    }
    UI::~UI() {
        delete root;
    }
    void UI::render() {
        root->render();
    }
    void UI::add_ui_object(UIObject *obj) {
        root->add_ui_object(obj);
    }
    
    void UI::click(float x, float y) {
        root->click(x, y);
    }
}