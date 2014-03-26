#include <glm/glm.hpp>
#include <iostream>

#include "button.hpp"

using namespace gewi;

static glm::vec2 verts[] = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
};

Button::Button() {
    mesh = new Mesh(GL_TRIANGLE_STRIP);
    mesh->load_vertex_data(4, verts);
}
Button::~Button() {
    delete mesh;
}