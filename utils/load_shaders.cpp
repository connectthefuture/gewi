#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "load_shaders.hpp"

using namespace std;

static GLuint compile_shader(const char *path, GLenum shader_type);

GLuint compile_shader(const char *path, GLenum shader_type) {
    //Read the file using a string stream
    ifstream fin;
    fin.open(path);
    if (!fin.good()) {
        cerr << "Failed to open shader file " << path << endl;
        exit(-1);
    }
    stringstream str_stream;
    str_stream << fin.rdbuf();
    string shader_source = str_stream.str();
    
    GLuint shader_id = glCreateShader(shader_type);
   
    char const *source_c_str = shader_source.c_str();
    glShaderSource(shader_id, 1, &source_c_str , NULL);
    glCompileShader(shader_id);
 
    // Check the compilation state of the shader
    GLint result = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int info_log_length;
        cerr << "Failed to compile " << path << endl;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        char *error_messages = new char[info_log_length];
        glGetShaderInfoLog(shader_id, info_log_length, NULL, &error_messages[0]);
        cerr << error_messages << endl;
        delete[] error_messages;
        exit(-1);
    }
    
    return shader_id;
}

unsigned load_shader(const char *vertex_shader, //Required shaders
                     const char *fragment_shader,
                     const char *geometry_shader,
                     const char *tesselation_shader_control,
                     const char *tesselation_shader) {
    
    GLuint vertex_id = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragment_id = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);
    
    // Link the program
    GLuint program_id = glCreateProgram();
    
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
 
    //Check for linking errors
    GLint result = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int info_log_length;
        cerr << "Failed to compiler shader\n";
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        char *error_messages = new char[info_log_length];
        glGetProgramInfoLog(program_id, info_log_length, NULL, &error_messages[0]);
        cerr << error_messages << endl;
        delete[] error_messages;
        exit(-1);
    }
    
    //Clean up the individual shaders
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    
    return program_id;
}