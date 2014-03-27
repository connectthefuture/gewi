#include "ui.hpp"

using namespace gewi;
UI::UI() {
    root = new UIContainer();
    flat_shader = new Renderer("gewi/render/shaders/flat_v.glsl",
                               "gewi/render/shaders/flat_f.glsl");
    texture_shader = new Renderer("gewi/render/shaders/texture_v.glsl",
                               "gewi/render/shaders/texture_f.glsl");
}

UI::~UI() {
    delete root;
    delete texture_shader;
    delete flat_shader;
}

void UI::render() {
    flat_shader->enable();
    root->render(flat_shader);
    //texture_shader->enable();
    //root->render(texture_shader);
}

void UI::add_ui_object(UIObject *obj) {
    root->add_child(obj);
}

void UI::click(float x, float y) {
    root->click(x, y);
}

void UI::key_press(int key, int mods) {
    root->key_press(key, mods);
}

void UI::layout() {
    root->calculate_dims();
    root->layout();
}