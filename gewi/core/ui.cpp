#include <iostream>
#include <SOIL/SOIL.h>


#include "ui.hpp"
#include "ui-element.hpp"
#include "layout-engine.hpp"

using namespace gewi;

UI::UI(int width, int height) {
    root = new UIElement();
    renderer = new Renderer("gewi/render/shaders/texture_v.glsl",
                            "gewi/render/shaders/texture_f.glsl");
    layout_engine = new UILayoutEngine();
    //Get the current viewport size
    this->width = width;
    this->height = height;
    
    root->set_dims(width, height);
}
UI::~UI() {
    delete root;
    delete renderer;
    delete layout_engine;
}

void UI::add_element(UIElement *elem) {
    //Add it to the root
    root->add_element(elem);
    elem->set_ui(this);
    elem->update_transform_matrix();
    //Add it to the render queue
    element_skin e;
    e.element = elem;
    unsigned tex = elem->get_texture();
    if (tex == 0)
        e.texture_id = skin_id;
    else
        e.texture_id = tex;
    render_queue.push_front(e);
}
void UI::layout() {
    layout_engine->layout(root);
}
void UI::render() {
    unsigned last = 0;
    renderer->enable();
    for (std::list<element_skin>::iterator it=render_queue.begin();
         it != render_queue.end();
         it++) {
        //Check if we need to bind a new texture
        if(it->texture_id != last) {
            glBindTexture(GL_TEXTURE_2D, it->texture_id);
            last = it->texture_id;
        }
        it->element->render(renderer);
    }
}

void UI::set_skin(const char *skin_path) {
    int img_width, img_height;
    unsigned char* img = SOIL_load_image(skin_path, &img_width, &img_height, NULL, 0);
    if (img == nullptr) std::cerr << "SOIL loading error: '" << SOIL_last_result() << "' (" << skin_path << ")" << std::endl;   
    glGenTextures(1, &skin_id);
    
    glBindTexture(GL_TEXTURE_2D, skin_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);    
}