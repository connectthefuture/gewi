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
    
    //Testing
    std::string font_file("/usr/share/fonts/truetype/freefont/FreeMono.ttf");
    FontAtlas *font = create_font_atlas(font_file, 40);
    font->bind_for_render();

    //Bootstrap a triangle
    /*unsigned triangle = create_triangle();
    //Load up the bootstrap shaders
    unsigned shader = load_shader("utils/bootstrap-shaders/bootstrap_v.glsl",
                                  "utils/bootstrap-shaders/bootstrap_f.glsl");*/
   
    unsigned shader1 = load_shader("gewi/render/shaders/texture_v.glsl",
                                   "gewi/render/shaders/texture_f.glsl");
    test_ui = new UI();
    
    //A simple button
    Button *test_button = new Button();
    test_button->set_click_callback(simple_click_callback);
    
    //Position the button
    test_button->set_dim(0.5, 0.5);
    
    test_ui->add_ui_object(test_button);
    
    //Enter the main loop
    while(!glfwWindowShouldClose(main_window)) {
        //glUseProgram(shader);
        //render_triangle(triangle);
        glUseProgram(shader1);
        test_ui->render();
        
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    
    //Clean up
    
    delete test_ui;
    
    glfwTerminate();
    
    return 0;
}