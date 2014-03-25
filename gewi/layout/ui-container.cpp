#include "ui-container.hpp"

using namespace gewi;

UIContainer::UIContainer() {
    parent = nullptr;
}

UIContainer::~UIContainer() {
    //Note, this does not explicitly destroy all children.
    //It is up to the end user to clean up properly.
}

void UIContainer::add_ui_object(UIObject *obj) {
    children.push_back(obj);
    //Tell the children I am their new parent
}

void UIContainer::render() {
    //Render myself
    
    //Render all my children
    for (unsigned i = 0; i < children.size(); i++) {
        children[i]->render();
    }
}

UIContainer *UIContainer::get_parent() { return parent; } 

void UIContainer::set_parent(UIContainer *parent) { this->parent = parent; }