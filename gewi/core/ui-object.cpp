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
    margin_top = 0.0f;
    transform_matrix = glm::mat4(1.0f);
    parent = nullptr;
    selected = false;
    click_callback = nullptr;
}

UIObject::~UIObject() {
    delete style;
}

void UIObject::render(Renderer *renderer) {
    if (mesh != nullptr) {
        glUniformMatrix4fv(renderer->transform_location, 1, GL_FALSE, &transform_matrix[0][0]);
        mesh->render();
    }
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->render(renderer);
    }
}

void UIObject::add_child(UIObject *child) {
    UIObject *last;
    if (children.size() != 0)
        last = children.back();
    else
        last = nullptr;
    children.push_back(child);
    child->set_parent(this);
    //Position the child properly
    //NOTE: For now we assume that each element will be on its own line, with x = 0;
    if (last != nullptr) {
        child->x = 0;
        child->y = last->y + last->height;
    }
    else {
        child->x = 0;
        child->y = 0;
    }
        
}

void UIObject::set_parent(UIObject *parent) {
    this->parent = parent;
}

void UIObject::update_transform() {
    transform_matrix = glm::translate(x * 2.0f - 1.0f, -(y + margin_top) * 2.0f + 1.0f, 0.0f) *
                       glm::scale(width * 2, -height * 2, 1.0f); // - height accounts for the fact that the UI coordinates start at the upper left
}

void UIObject::apply_style() {
    //Get the width/height
    std::string result = style->get_style("width");
    if (result != "") {
        float value = style_to_dim(result, parent);
        if (result.back() == '%') width = parent->width * value;
        else width = value;
    }
    
    result = style->get_style("height");
    if (result != "") {
        float value = style_to_dim(result, parent);
        if (result.back() == '%') height = parent->height * value;
        else height = value;
    }
    
    result = style->get_style("margin-top");
    if (result != "") {
        float value = style_to_dim(result, parent);
        if (result.back() == '%') margin_top = parent->height * value;
        else margin_top = value;
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
    return (this->x < x && this->x + width > x &&
            this->y < y && this->y + height > y);
}
void UIObject::click(float x, float y) {
    if (contains_point(x, y)) {
        if (click_callback != nullptr) {
            click_callback(x, y);
        }
        //Send down to all children
        for (unsigned i = 0; i < children.size(); i++) {
            children[i]->click(x, y);
        }
    }
}

void UIObject::set_click_callback(void (*callback)(float, float)) {
    click_callback = callback;
}