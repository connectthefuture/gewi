#include <iostream>

#include <glm/gtx/transform.hpp>

#include "../core/ui.hpp"
#include "text.hpp"

using namespace gewi;
Text::Text() { 
    atlas = nullptr;
}
Text::~Text() { }

Text::Text(FontAtlas *atlas, std::string text) { 
    this->atlas = atlas;
    this->text = text;
}


float Text::add_char(char c, float &base_x, float base_y, glm::vec2 *vert, glm::vec2 *tex) {
    char_position c_pos = atlas->char_lookup(c);
    
    //TODO: Use GLFW to get the actual screen size
    float px = 2.0f / container->get_width();
    float py = 2.0f / container->get_height();

    float x, y, w, h;
    x = base_x * px + c_pos.left * px;
    y = base_y * py + c_pos.top * py;
    
    w = c_pos.width * px;
    h = -c_pos.height * py;
    
    //std::cout << x << " " << y << '\n';
    
    *vert++ = glm::vec2(x, y);
    *vert++ = glm::vec2(x + w, y);
    *vert++ = glm::vec2(x, y + h);
    
    *vert++ = glm::vec2(x + w, y);
    *vert++ = glm::vec2(x, y + h);
    *vert++ = glm::vec2(x + w, y + h);
    
    *tex++ = glm::vec2(c_pos.x1, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y2);
    
    base_x += (c_pos.advance >> 6);
    
    return c_pos.height;
}

void Text::set_text(std::string text) {
    if (mesh != nullptr) delete mesh; //Should I reuse the mesh?
    this->text = text;
    
    mesh = new Mesh(GL_TRIANGLES);
    unsigned num_letters = text.size();
    glm::vec2 *verts = new glm::vec2[num_letters * 6];
    glm::vec2 *tex = new glm::vec2[num_letters * 6];
    
    glm::vec2 *current_vertex, *current_tex;
    current_tex = tex;
    current_vertex = verts;
    float x = 0, y = 0;
    max_height = 0;
    for (unsigned i = 0; i < num_letters; i++) {
        float h = add_char(text[i], x, y, current_vertex, current_tex);
        if (h > max_height) max_height = h;
        current_vertex += 6;
        current_tex += 6;
    }
    
    mesh->load_vertex_data(num_letters * 6, verts);
    mesh->load_tex_coords(num_letters * 6, tex);
    
    delete[] verts;
    delete[] tex;
    
    width = x;
    height = max_height;
}

void Text::update_transform_matrix() {
    if(container == nullptr) return;
    float gx, gy;
    gx = (x / (float) container->get_width()) * 2.0f - 1.0f;
    gy = 1.0f - ((y + max_height) / (float) container->get_height()) * 2.0f;
    glm::mat4 translate_mat = glm::translate(gx, gy, 0.0f);
    transform_matrix = translate_mat;
}

unsigned Text::get_texture() {
    return atlas->get_texture();
}

void Text::set_ui(UI *ui) {
    container = ui;
    //Generate a mesh
    set_text(this->text);
    update_transform_matrix();
    ui->render_register(this);
}