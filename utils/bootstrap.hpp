#ifndef UTILS_BOOTSTRAP
#define UTILS_BOOTSTRAP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Initialize GLFW, OpenGL, GLEW, and anything
//else that needs to be initialized.
void initialize(bool verbose = false);

//Creates a window and handles error checking and OpenGL/glew initialization.
GLFWwindow *create_window(unsigned width, unsigned height, const char *name, bool verbose = false);

#endif