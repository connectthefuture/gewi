#include <iostream>
#include <sstream>

#include <glm/gtx/transform.hpp>

#include "ui-object.hpp"

using namespace gewi;

//Converts from something like 50% to an actual number openGL can
//use like 0.5f;
/*static float style_to_dim(std::string style, UIObject *parent) {
    int val;
    std::stringstream ss;
    ss.str(style);
    ss >> val;
    if (style.back() == '%') {
        assert (parent != nullptr);
        return val / 100.0f;
    }
    return (float) val;
}*/

UIObject::UIObject() {
    mesh = nullptr;
    style = new Style;
    x = y = 0.0f;
    width = height = 1.0f;
    margin_top = margin_left = margin_right = margin_bottom = 0.0f;
    transform_matrix = glm::mat4(1.0f);
    parent = nullptr;
    selected = false;
    click_callback = nullptr;
    containing_width = 0.0f;
    containing_height = 0.0f;
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
    children.push_back(child);
    child->set_parent(this);    
}

void UIObject::set_parent(UIObject *parent) {
    this->parent = parent;
}

void UIObject::update_transform() {
    transform_matrix = glm::translate(x * 2.0f - 1.0f,  -1.0f + y * 2.0f, 0.0f) * //Convert from 0,0 at the upper left to 0, 0 in the center
                       glm::scale(width, height, 1.0f); // - height accounts for the fact that the UI coordinates start at the bottom left
}

UIObject *UIObject::get_parent() {
    return parent;
}

//Methods for changing style
void UIObject::set_style(std::string key, std::string value) {
    style->set_style(key, value);
}
std::string UIObject::get_style(std::string key) {
    return style->get_style(key);
}

void UIObject::calculate_dims() {
    width = containing_width;
    height = containing_height;
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->calculate_dims();
        width += children[i]->width;
        height += children[i]->height;
    }
    if (parent == nullptr) { //Make sure the root covers everything
        width = 1.0f;
        height = 1.0f;
    }
    
    std::cout << width << std::endl;
}

void UIObject::layout() {
    float current_x = x;
    float current_y = y;
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->x = current_x;
        children[i]->y = current_y;
        children[i]->layout();
        current_x += children[i]->width;
    }
    update_transform();
}


void UIObject::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
}


//Methods for interaction
bool UIObject::contains_point(float x, float y) {
    return (this->x < x && this->x + width > x &&
            this->y < y && this->y + height > y);
}
void UIObject::click(float x, float y) {
    if (contains_point(x, y)) {
        click_handler(x, y); //Run internal callback then external callback
        if (click_callback != nullptr) {
            click_callback(x, y);
        }
        //Send down to all children
        for (unsigned i = 0; i < children.size(); i++) {
            children[i]->click(x, y);
        }
    }
}

void UIObject::key_press(int key, int mods) {
    key_press_handler(key, mods);
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->key_press(key, mods);
    }
}

void UIObject::set_click_callback(void (*callback)(float, float)) {
    click_callback = callback;
}
