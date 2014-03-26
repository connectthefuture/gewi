#include "../../utils/load_shaders.hpp"
#include "ui.hpp"

using namespace gewi;
UI::UI() {
    root = new UIContainer();
    //flat_shader = load_shader("gewi/render/shaders/flat_v.glsl",
    //                          "gewi/render/shaders/flat_f.glsl");
}

UI::~UI() {
    delete root;
}

void UI::render() {
    root->render();
}

void UI::add_ui_object(UIObject *obj) {
    root->add_child(obj);
}

void UI::click(float x, float y) {
    root->click(x, y);
}
