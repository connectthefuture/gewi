#ifndef GEWI_CORE_UI
#define GEWI_CORE_UI

#include <list>

#include "../render/renderer.hpp"

namespace gewi {
    class UILayoutEngine;
    class UIElement;
    
    typedef struct element_skin {
        unsigned texture_id;
        UIElement *element;
    } element_skin;
    
    class UI {
    private:
        UILayoutEngine *layout_engine;
        UIElement *root;
        unsigned shader_id;
        unsigned skin_id;
        
        //Render queue, sorted by the texture_id that they require.
        std::list<element_skin> render_queue;
        Renderer *renderer;
        int width, height;
    public:
        UI(int width, int height);
        ~UI();
        
        void add_element(UIElement *elem);
        void layout(); //Use the current layout engine to layout the elements starting from the root.
        void render(); //Render the UI. Assumes layout has already been called and is accurate.
        
        void render_register(UIElement *elem);
        
        //Set the skin
        void set_skin(const char *skin_path);
        
        //Interaction code
        void click(float x, float y);
        
        //Getters and setters
        int get_width() { return width; }
        int get_height() { return height; } 
        
        void resize(int width, int height);
    };
}
#endif