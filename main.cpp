/***********************************************
 * This is a very simple test of gewi. It is
 * intended for use during development, but 
 * should not be included in any final releases.
 * It makes extensive use of the bootstrapping
 * code provided by the utils/bootstrap
************************************************/

#include <iostream>

#include "gewi/gewi.hpp"
#include "utils/bootstrap.hpp"
#include "utils/load_shaders.hpp"
#include "utils/font_atlas.hpp"

#include <SOIL/SOIL.h>

using namespace gewi; //Make sure we use the gewi namespace

static UI *test_ui = nullptr;

void simple_click_callback() {
    std::cout << "Click callback triggered\n";
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        int width, height;
        glfwGetCursorPos(window, &x, &y);
        glfwGetWindowSize(window, &width, &height);
        //Normalize the coordinates to device space
        x = (2.0f * x) / width - 1.0f;
        y = 1.0f - (2.0f * y) / height;
        test_ui->click(x, y);
    }
}

int main(int argc, char **argv) {
    initialize(true); //Use the bootstrap initializer and window creation
    GLFWwindow *main_window = create_window(640, 480, "GEWI test", true);
    //Register our callbacks
    glfwSetMouseButtonCallback(main_window, mouse_callback);
    
    test_ui = new UI();
    
    Button *test_button = new Button();
    test_ui->add_ui_object(test_button);
    
    test_button->set_style("width", "100%");
    
    //Enter the main loop
    while(!glfwWindowShouldClose(main_window)) {
        test_ui->render();
        
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    
    //Clean up
    delete test_ui;
    delete test_button;
    
    glfwTerminate();
    
    return 0;
}