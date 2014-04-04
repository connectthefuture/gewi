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
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        test_ui->click(x, y);
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    test_ui->resize(width, height);
}

int main(int argc, char **argv) {
    initialize(true); //Use the bootstrap initializer and window creation
    GLFWwindow *main_window = create_window(640, 480, "GEWI test", true);
    //Register our callbacks
    glfwSetMouseButtonCallback(main_window, mouse_callback);
    //glfwSetKeyCallback(main_window, key_callback);
    glfwSetWindowSizeCallback(main_window, window_size_callback);
    
    test_ui = new UI(640, 480);
    test_ui->set_skin("test.png");
    
    //Load up the font atlas
    std::string font_file("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
    FontAtlas *atlas = new FontAtlas(font_file, 20);
    
    Text *test_text_1 = new Text(atlas, std::string("test1 tauboesrcuaoehucaoerbu aoecuhaeouaoeuoeauoe"));
    Text *test_text_2 = new Text(atlas, std::string("test2"));
    
    Button *test_button_1 = new Button();
    Button *test_button_2 = new Button();
    
    test_button_1->add_element(test_text_1);
    test_button_1->add_element(test_text_2);
    
    test_button_2->set_style("height", "100");
    test_button_2->set_style("width", "100");
    //test_button_2->set_style("x", "100");
    //test_button_2->set_style("y", "100");
    //test_button_2->set_style("position", "absolute");
    
    test_button_1->install_click_callback(simple_click_callback);
    test_button_2->install_click_callback(simple_click_callback);
    
    test_ui->add_element(test_button_1);
    test_ui->add_element(test_button_2);
    
    test_ui->layout();
   
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    //Open GL configuration
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
    
    glfwTerminate();
    
    return 0;
}