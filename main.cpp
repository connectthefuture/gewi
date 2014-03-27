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

void simple_click_callback(float x, float y) {
    std::cout << "Click callback triggered\n";
    //test_text->set_text("clicked!");
}

/*void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        int width, height;
        glfwGetCursorPos(window, &x, &y);
        glfwGetWindowSize(window, &width, &height);
        //Normalize the coordinates to device space
        x /= width;
        y /= height;
       //test_ui->click(x, y);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { 
    if (action != GLFW_RELEASE) {
        //test_ui->key_press(key, mods);
    }
}*/

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
    initialize(true); //Use the bootstrap initializer and window creation
    GLFWwindow *main_window = create_window(640, 480, "GEWI test", true);
    //Register our callbacks
    //glfwSetMouseButtonCallback(main_window, mouse_callback);
    //glfwSetKeyCallback(main_window, key_callback);
    glfwSetWindowSizeCallback(main_window, window_size_callback);
    
    test_ui = new UI(640, 480);
    test_ui->set_skin("test.png");
    
    /*******************************************************************
     * In this test UI we have 2 static texts, a text input and and two
     * buttons. On top there should be a text followed by a button. Below
     * that should be a text, a text input and a button
    ******************************************************************/
    
    //Load up the font atlas
    //std::string font_file("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
    //FontAtlas *atlas = new FontAtlas(font_file, 50);
    
    //Text *test_text_1 = new Text(atlas, std::string("test1"));
    //Text *test_text_2 = new Text(atlas, std::string("test2"));
    Button *test_button_1 = new Button();
    Button *test_button_2 = new Button();
    
    test_button_1->set_dims(100, 100);
    test_button_2->set_dims(570, 50);
   
    test_ui->add_element(test_button_2);
    test_ui->add_element(test_button_1);
    
    test_ui->layout();
    
    
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