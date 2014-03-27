#include <iostream>
#include <glm/gtx/transform.hpp>

#include "ui.hpp"
#include "ui-element.hpp"


using namespace gewi;

UIElement::UIElement() {
    mesh = nullptr;
    container = nullptr;
    x = y = width = height = 0.0f;
    transform_matrix = glm::mat4(1.0f);
}
UIElement::~UIElement() {
    if (mesh != nullptr) delete mesh;
}

void UIElement::add_element(UIElement *elem) {
    children.push_back(elem);
    elem->parent = this;
}

//Simple setters and getters
void UIElement::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
    update_transform_matrix();
}
void UIElement::set_dims(float width, float height) {
    this->width = width;
    this->height = height;
    update_transform_matrix();
}

void UIElement::update_transform_matrix() {
    if (container == nullptr) return;
    //Convert from pixel to openGL coordinates
    float gx, gy, g_width, g_height;
    gx = (x / (float) container->get_width()) * 2.0f - 1.0f;
    gy = 1.0f - (y / (float) container->get_height()) * 2.0f;
    
    g_width = 2.0f * width / (float) container->get_width();
    g_height = 2.0f * -height / (float) container->get_height(); //Negate the height to flip y coordinates
    
    
    glm::mat4 translate_mat = glm::translate(gx, gy, 0.0f);
    glm::mat4 scale_mat = glm::scale(g_width, g_height, 1.0f);
    
    transform_matrix = translate_mat * scale_mat;
}


void UIElement::render(Renderer *renderer) {
    if (mesh != nullptr) {
        glUniformMatrix4fv(renderer->transform_location, 1, GL_FALSE, &transform_matrix[0][0]);
        this->mesh->render();
    }
}

void UIElement::set_ui(UI *ui) {
    container = ui;
}