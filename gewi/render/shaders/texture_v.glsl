#version 410 core

layout(location = 0) in vec2 coord;
layout(location = 1) in vec2 tex_coord;

out vec2 f_tex_coord;

uniform mat4 transform_matrix;

void main() {
    gl_Position = transform_matrix * vec4(coord, 0.0, 1.0);
    f_tex_coord = tex_coord;
}