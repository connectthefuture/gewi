#include <glm/glm.hpp>
#include <iostream>

#include "button.hpp"

using namespace gewi;

static glm::vec2 verts[] = {
    glm::vec2(-1.0f, -1.0f),
    glm::vec2(-1.0f, 1.0f),
    glm::vec2(1.0f, -1.0f),
    glm::vec2(1.0f, 1.0f),
};

static glm::vec2 tex[] = {
    glm::vec2(0.0, 0.0),
    glm::vec2(0.0, 1.0),
    glm::vec2(1.0, 0.0),
    glm::vec2(1.0, 1.0),
};


Button::Button() {
    mesh = nullptr;
    mesh = new Mesh(GL_TRIANGLE_STRIP);
    mesh->load_vertex_data(4, verts);
    mesh->load_tex_coords(4, tex);
}
Button::~Button() {
    delete mesh;
}

void Button::change_position_or_size() {
    //Really this should be done with matriacies
    glm::vec2 new_verts[] = {
        glm::vec2(x - width, y - height),
        glm::vec2(x - width, y + height),
        glm::vec2(x + width, y - height),
        glm::vec2(x + width, y + height)
    };
    
    for (int i = 0; i < 4; i++) {
        std::cout << new_verts[i][0] << ' ' << new_verts[i][1] << '\n';
    }
    mesh->update_vertex_data(4, new_verts);
}

//Note, this assumes the proper shader is already bound.
void Button::render() {
    mesh->render();
}