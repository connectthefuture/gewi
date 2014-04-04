#include <GL/glew.h>

#include "load_shaders.hpp"
#include "renderer.hpp"

using namespace gewi;

Renderer::Renderer(const char *vertex_shader, const char *fragment_shader) {
    shader_id = load_shader(vertex_shader, fragment_shader);
    transform_location = glGetUniformLocation(shader_id, "transform_matrix");
    mode_location = glGetUniformLocation(shader_id, "mode");
}

Renderer::~Renderer() { }

void Renderer::enable() {
    glUseProgram(shader_id);
}