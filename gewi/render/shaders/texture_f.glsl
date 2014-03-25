#version 410 core

in vec2 f_tex_coord;

out vec4 frag_color;

uniform sampler2D texture_sampler;

const vec3 COLOR = vec3(1, 1, 1);
 
void main(){
    float a = texture(texture_sampler, f_tex_coord).r;
    if (a == 0.0) discard;
    frag_color = vec4(COLOR * a, 1.0);
}