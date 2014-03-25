#include <iostream>

#include <stdlib.h>

#include "bootstrap.hpp"

using namespace std;


void initialize(bool verbose) {    
    if(!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }
    if (verbose) cout << "Initialized GLFW\n";
}


GLFWwindow *create_window(unsigned width, unsigned height, const char *name, bool verbose) {
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window) {
        cerr << "Failed to create a GLFW window\n";
        exit(-1);
    }
    if (verbose) cout << "Created a GLFW window\n";
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n";
        exit(-1);
    }
    if (verbose) {
        const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString (GL_VERSION); // version as a string
        cout << "Renderer: " << renderer << '\n';
        cout << "OpenGL version: " << version << '\n';
    }
    return window;
}

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

GLuint create_triangle() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    
    GLuint vertexbuffer;
 
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    return vao_id;

}

void render_triangle(GLuint vao_id) {
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}