#include <iostream>
#include <sstream>

#include <glm/gtx/transform.hpp>

#include "ui-object.hpp"

using namespace gewi;

//Converts from something like 50% to an actual number openGL can
//use like 0.5f;
static float style_to_dim(std::string style, UIObject *parent) {
    int val;
    std::stringstream ss;
    ss.str(style);
    ss >> val;
    if (style.back() == '%') {
        assert (parent != nullptr);
        return val / 100.0f;
    }
    return (float) val;
}

UIObject::UIObject() {
    mesh = nullptr;
    style = new Style;
    x = y = 0.0f;
    width = height = 1.0f;
    transform_matrix = glm::mat4(1.0f);
    parent = nullptr;
    selected = false;
    click_callback = nullptr;
}

UIObject::~UIObject() {
    delete style;
}

void UIObject::render() {
    if (mesh != nullptr) mesh->render();
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->render();
    }
}

void UIObject::add_child(UIObject *child) {
    children.push_back(child);
    child->set_parent(this);
}

void UIObject::set_parent(UIObject *parent) {
    this->parent = parent;
    //Update everything
}

void UIObject::update_transform() {
    transform_matrix = glm::scale(width, 0.0f, height);
}

void UIObject::apply_style() {
    //Get the width/height
    std::string result = style->get_style("width");
    if (result != "") {
        float value = style_to_dim(result, parent);
        if (result.back() == '%') width = parent->width * value;
        else width = value;
    }
    
    //Create the new matrices
    update_transform();
}

UIObject *UIObject::get_parent() {
    return parent;
}

//Methods for changing style
void UIObject::set_style(std::string key, std::string value) {
    style->set_style(key, value);
    apply_style();
}
std::string UIObject::get_style(std::string key) {
    return style->get_style(key);
}

//Methods for interaction
bool UIObject::contains_point(float x, float y) {
    return (this->x <= x && this->x + width >= x &&
            this->y <= y && this->y + height >= y);
}
void UIObject::click(float x, float y) {
    if (contains_point(x, y)) {
        std::cout << "Clicked!";
    }
}