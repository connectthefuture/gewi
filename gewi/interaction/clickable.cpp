#include "clickable.hpp"

using namespace gewi;

void Clickable::set_click_callback(void (*callback)()) { 
    this->click_callback = callback;
}