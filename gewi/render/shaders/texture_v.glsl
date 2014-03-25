#version 410 core

layout(location = 0) in vec2 coord;
layout(location = 1) in vec2 tex_coord;

out vec2 f_tex_coord;

void main() {
    gl_Position = vec4(coord, 0.0, 1.0);
    f_tex_coord = tex_coord;
}