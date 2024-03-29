#include "mesh.hpp"

using namespace gewi;

Mesh::Mesh(GLenum prim_type) : prim_type(prim_type) {
    glGenVertexArrays(1, &vao_id);
    vbuf_id = 0;
    texbuf_id = 0;
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao_id);
    if (vbuf_id != 0) glDeleteBuffers(1, &vbuf_id);
    if (texbuf_id != 0) glDeleteBuffers(1, &texbuf_id);
}
void Mesh::load_vertex_data(unsigned num_vertices, glm::vec2 *verts) {
    this->num_vertices = num_vertices;
    glBindVertexArray(vao_id);
    glGenBuffers(1, &vbuf_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf_id);
    
    //Pass on the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_vertices, verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Mesh::load_tex_coords(unsigned num_vertices, glm::vec2 *tex_coords) {
    assert(this->num_vertices == num_vertices);
    glBindVertexArray(vao_id);
    glGenBuffers(1, &texbuf_id);
    glBindBuffer(GL_ARRAY_BUFFER, texbuf_id);
    
    //Pass on the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_vertices, tex_coords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Mesh::update_vertex_data(unsigned num_vertices, glm::vec2 *verts) {
    assert(this->num_vertices == num_vertices);
    
    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf_id);
    
    //Pass on the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * num_vertices, verts);
}
void Mesh::render() {
    glBindVertexArray(vao_id);
    glDrawArrays(prim_type, 0, num_vertices);
}