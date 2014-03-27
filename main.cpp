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
#include "utils/fps.hpp"

#include <SOIL/SOIL.h>

using namespace gewi; //Make sure we use the gewi namespace

static UI *test_ui = nullptr;
//static Text *test_text = nullptr;

void simple_click_callback(float x, float y) {
    std::cout << "Click callback triggered\n";
    //test_text->set_text("clicked!");
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        int width, height;
        glfwGetCursorPos(window, &x, &y);
        glfwGetWindowSize(window, &width, &height);
        //Normalize the coordinates to device space
        x /= width;
        y /= height;
        test_ui->click(x, y);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { 
    if (action != GLFW_RELEASE) {
        test_ui->key_press(key, mods);
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
    initialize(true); //Use the bootstrap initializer and window creation
    GLFWwindow *main_window = create_window(640, 480, "GEWI test", true);
    //Register our callbacks
    glfwSetMouseButtonCallback(main_window, mouse_callback);
    glfwSetKeyCallback(main_window, key_callback);
    glfwSetWindowSizeCallback(main_window, window_size_callback);
    
    test_ui = new UI();
    
    //Load up the font atlas
    std::string font_file("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
    FontAtlas *atlas = new FontAtlas(font_file, 18);
    
    TextInput *test_input = new TextInput(atlas);
    test_ui->add_ui_object(test_input);
    /*test_text = new Text(atlas, "the quick brown fox jumped over the lazy dog");
   
    
    Button *test_button = new Button();
    test_ui->add_ui_object(test_button);
    
    test_button->set_style("width", "50%");
    test_button->set_style("height", "10%");
    test_button->set_click_callback(simple_click_callback);
    
    test_ui->add_ui_object(test_text);*/
    /*
    
    Button *test_button1 = new Button();
    test_ui->add_ui_object(test_button1);
    
    test_button1->set_style("width", "30%");
    test_button1->set_style("height", "10%");
    test_button1->set_style("margin-top", "30%");
    test_button1->set_click_callback(simple_click_callback);*/
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    //Enter the main loop
    while(!glfwWindowShouldClose(main_window)) {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        fps_counter();
        test_ui->render();
        
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    
    //Clean up
    delete test_ui;
   // delete test_text;
    
    glfwTerminate();
    
    return 0;
}