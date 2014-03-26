#include "ui.hpp"

using namespace gewi;
UI::UI() {
    root = new UIContainer();
    flat_shader = new Renderer("gewi/render/shaders/flat_v.glsl",
                               "gewi/render/shaders/flat_f.glsl");
}

UI::~UI() {
    delete root;
}

void UI::render() {
    flat_shader->enable();
    root->render(flat_shader);
}

void UI::add_ui_object(UIObject *obj) {
    root->add_child(obj);
}

void UI::click(float x, float y) {
    root->click(x, y);
}
