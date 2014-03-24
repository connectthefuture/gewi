#ifndef UTILS_LOAD_SHADERS
#define UTILS_LOAD_SHADERS

//Reads in and complies shaders, prints to stderr if there was
//an error.
unsigned load_shader(const char *vertex_shader, //Required shaders
                     const char *fragment_shader,
                     const char *geometry_shader = nullptr,
                     const char *tesselation_shader_control = nullptr,
                     const char *tesselation_shader = nullptr);
#endif