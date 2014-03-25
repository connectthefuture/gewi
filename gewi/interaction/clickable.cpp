#include "clickable.hpp"

#include <iostream>
using namespace gewi;

Clickable::Clickable() { 
    click_callback = nullptr; 
}
Clickable::~Clickable() { }
        
void Clickable::set_click_callback(void (*callback)()) { 
    this->click_callback = callback;
}

void Clickable::click(float x, float y) {
    if (this->x - width < x &&
        this->x + width > x &&
        this->y - height < y &&
        this->y + height > y) {
        internal_click_callback(x, y);
        if(click_callback != nullptr)
            click_callback();
    }
    //std::cout << x << " " << y;
}