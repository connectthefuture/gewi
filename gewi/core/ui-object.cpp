#include "ui-object.hpp"

using namespace gewi;

UIObject::UIObject() {
    x = y = width = height = 0.0f;
}

void UIObject::set_xy(float x, float y) { 
    this->x = x;
    this->y = y;
    change_position_or_size();
}

void UIObject::set_dim(float width, float height) {
    this->width = width;
    this->height = height;
    change_position_or_size();
}

void UIObject::get_xy(float &x, float &y) {
    x = this->x;
    y = this->y;
}

void UIObject::get_dim(float &width, float &height) {
    width = this->width;
    height = this->height;
}