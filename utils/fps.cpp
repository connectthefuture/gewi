#include <GLFW/glfw3.h>
#include <iostream>

#include "fps.hpp"

void fps_counter() {
    static double last_time = glfwGetTime();
    static int num_frames = 0;
    
    double current_time = glfwGetTime();
    num_frames++;
    if (current_time - last_time >= 1.0) {
        std::cout << num_frames / (current_time - last_time) << " fps\n";
        num_frames = 0;
        last_time = current_time;
    }
}
