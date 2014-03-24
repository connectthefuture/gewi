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