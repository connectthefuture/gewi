#include <iostream>
#include "text.hpp"

using namespace gewi;
/*
static glm::vec2 verts[] = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
};

static glm::vec2 tex_coords[] = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
};

*/

void Text::add_char(char c, float &base_x, float base_y, glm::vec2 *vert, glm::vec2 *tex) {
    char_position c_pos = atlas->char_lookup(c);
    
    //TODO: Use GLFW to get the actual screen size
    float px = 2.0f / 640.0f;
    float py = 2.0f / 480.0f;
    float x, y, w, h;
    x = base_x + c_pos.left * px;
    y = -base_y - c_pos.top * py;
    
    w = c_pos.width * px;
    h = c_pos.height * py;
    
    *vert++ = glm::vec2(x, -y);
    *vert++ = glm::vec2(x + w, -y);
    *vert++ = glm::vec2(x, -y - h);
    
    *vert++ = glm::vec2(x + w, -y);
    *vert++ = glm::vec2(x, -y - h);
    *vert++ = glm::vec2(x + w, -y - h);
    
    *tex++ = glm::vec2(c_pos.x1, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y2);
    
    base_x += (c_pos.advance >> 6) * px;
}

Text::Text(FontAtlas *atlas, std::string text) {
    this->atlas = atlas;
    
    
    mesh = new Mesh(GL_TRIANGLES);
    unsigned num_letters = text.size();
    std::cout << num_letters << '\n';
    glm::vec2 *verts = new glm::vec2[num_letters * 6];
    glm::vec2 *tex = new glm::vec2[num_letters * 6];
    
    glm::vec2 *current_vertex, *current_tex;
    current_tex = tex;
    current_vertex = verts;
    float x = 0, y = 0;
    for (unsigned i = 0; i < num_letters; i++) {
        add_char(text[i], x, y, current_vertex, current_tex);
        current_vertex += 6;
        current_tex += 6;
    }
    
    mesh->load_vertex_data(num_letters * 6, verts);
    mesh->load_tex_coords(num_letters * 6, tex);
    
    delete[] verts;
    delete[] tex;
    
}
Text::~Text() {
    delete mesh;
}
//Text will never have children. It will always be a leaf
void Text::render(Renderer *renderer) {
    atlas->bind_for_render();
    if (mesh != nullptr) {
        glUniformMatrix4fv(renderer->transform_location, 1, GL_FALSE, &transform_matrix[0][0]);
        mesh->render();
    }
}