#version 410 core

in vec2 f_tex_coord;

out vec4 frag_color;

uniform sampler2D texture_sampler;

const vec3 COLOR = vec3(1, 1, 1);
 
void main(){
    vec3 a = texture(texture_sampler, f_tex_coord);
    if (a.r == 0.0 && a.g == 0 && a.b == 0) discard;
    frag_color = vec4(a, 1.0);
}