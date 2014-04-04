#version 410 core

in vec2 f_tex_coord;

out vec4 frag_color;

uniform sampler2D texture_sampler;

const int SKIN_MODE = 0;
const int TEXT_MODE = 1;
uniform int mode;

const vec3 COLOR = vec3(1, 1, 1);
 
void main(){
    if(mode == SKIN_MODE) frag_color = vec4(texture(texture_sampler, f_tex_coord).rgb, 1);
    else {
        float val = texture(texture_sampler, f_tex_coord).r;
        frag_color = vec4(1, 0, 0, val);
    }
}