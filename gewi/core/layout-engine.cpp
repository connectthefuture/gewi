#include <iostream>

#include "layout-engine.hpp"
#include "ui-element.hpp"
using namespace gewi;

void UILayoutEngine::calculate_dimensions(UIElement *root) { }
void UILayoutEngine::calculate_layout(UIElement *root) { 
    float current_x = root->x;
    float current_y = root->y;
    float y_advance = 0.0f;
    std::cout << "In here " << root->children.size() << "\n";
    for (unsigned i = 0; i < root->children.size(); i++) {
        //Check for overflow and line break.
        if (current_x + root->children[i]->width > root->width) {
            current_x = 0;
            current_y += y_advance;
        }
        root->children[i]->set_pos(current_x, current_y);
        
        current_x += root->children[i]->width;
        y_advance = std::max(y_advance, root->children[i]->height);
    }
}
void UILayoutEngine::layout(UIElement *root) { 
    calculate_dimensions(root);
    calculate_layout(root);
}