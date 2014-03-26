#include <iostream>
#include "text.hpp"

using namespace gewi;

Text::Text(FontAtlas *atlas, std::string text) {
    this->atlas = atlas;
    /*unsigned num_verts = text.length() * 6;
    
    glm::vec2 *verts = new glm::vec2[num_verts];
    glm::vec2 *tex = new glm::vec2[num_verts];
    
    glm::vec2 *vert_current = verts;
    glm::vec2 *tex_current = tex;
    float x = 0.0f;
    for (unsigned i = 0; i < text.length(); i++) {
        char_position pos = atlas->char_lookup(text[i]);
        
        *vert_current++ = glm::vec2(x, 0.0f);
        *vert_current++ = glm::vec2(x, pos.height);
        *vert_current++ = glm::vec2(x + pos.width, 0.0f);
        //Second triangle
        *vert_current++ = glm::vec2(x + pos.width, 0.0f);
        *vert_current++ = glm::vec2(x + pos.width, pos.height);
        *vert_current++ = glm::vec2(x, pos.height);
        
        x += pos.width;
        //Load up texture coordinates
        std::cout << pos.x1 << " " << pos.y1 << " " << pos.x2 << " " << pos.y2 << '\n';
        
        *tex_current++ = glm::vec2(pos.x1, pos.y2);
        *tex_current++ = glm::vec2(pos.x1, pos.y1);
        *tex_current++ = glm::vec2(pos.x2, pos.y2);
        
        *tex_current++ = glm::vec2(pos.x2, pos.y2);
        *tex_current++ = glm::vec2(pos.x2, pos.y1);
        *tex_current++ = glm::vec2(pos.x1, pos.y1);
        
    }
    
    mesh = new Mesh(GL_TRIANGLES);
    mesh->load_vertex_data(num_verts, verts);
    mesh->load_tex_coords(num_verts, tex);
    delete[] verts;
    delete[] tex;*/
    
    mesh = new Mesh(GL_TRIANGLES);
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