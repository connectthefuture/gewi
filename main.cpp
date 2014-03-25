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

using namespace gewi; //Make sure we use the gewi namespace

void simple_click_callback() {
    std::cout << "Click callback triggered\n";
}

int main(int argc, char **argv) {
    initialize(true); //Use the bootstrap initializer and window creation
    GLFWwindow *main_window = create_window(640, 480, "GEWI test", true);
    
    UI *test_ui = new UI();
    
    //A simple button
    Button *test_button = new Button();
    test_button->set_click_callback(simple_click_callback);
    /*
    //Create some simple widgets
    Text *test_text = new Text("This is some test text", "some font.ttf", 12);
    
    
    //Install callbacks
    test_button->set_callback(simple_click_callback);
    
    //Add the widgets to the ui
    test_ui->add_widget(test_text, -0.5f, -0.5f);
    test_ui->add_widget(test_button, 0.0f, 0.0f);*/
    
    //Enter the main loop
    while(!glfwWindowShouldClose(main_window)) {
        test_ui->render();
        
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    
    //Clean up
    
    delete test_ui;
    
    glfwTerminate();
    
    return 0;
}