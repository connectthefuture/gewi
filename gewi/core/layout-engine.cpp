#include <iostream>
#include <string>

#include "layout-engine.hpp"
#include "ui-element.hpp"
using namespace gewi;

void UILayoutEngine::calculate_dimensions(UIElement *root) {
    float width = 0.0f;
    float height = 0.0f;
    for (unsigned i = 0; i < root->children.size(); i++) {
        //Recurse on children
        calculate_dimensions(root->children[i]);
        width += root->children[i]->width;
        height = std::max(root->children[i]->height, height);
    }
    //Check for style elements
    std::string result;
    
    root->style->get_style("width", width);
    root->style->get_style("height", height);
    
    root->set_dims(width, height);
}
void UILayoutEngine::calculate_layout(UIElement *root) { 
    float current_x = root->x;
    float current_y = root->y;
    float y_advance = 0.0f;
    float height = 0.0f;
    for (unsigned i = 0; i < root->children.size(); i++) {
        //Check if this is absolutely positioned
        std::string result;
        if (root->children[i]->style->get_style("position", result) &&
            result == "absolute") {
            float x, y;
            root->children[i]->style->get_style("x", x);
            root->children[i]->style->get_style("y", y);
            root->children[i]->set_pos(x, y);
            calculate_layout(root->children[i]);
       
            continue;
        }
        
        //Check for overflow and line break.
        if (current_x + root->children[i]->width > root->width + root->x) {
            current_x = 0;
            current_y += y_advance;
            height += y_advance;
            y_advance = 0.0f;
        }
        
        root->children[i]->set_pos(current_x, current_y);
        //Run layout calculations
        calculate_layout(root->children[i]);
        
        current_x += root->children[i]->width;
        y_advance = std::max(y_advance, root->children[i]->height);
    }
    height += y_advance;
    //Update my height which may have changed due to line breaks
    root->style->get_style("height", height);
    root->set_dims(root->width, height);
}
void UILayoutEngine::layout(UIElement *root) { 
    calculate_dimensions(root);
    calculate_layout(root);
}