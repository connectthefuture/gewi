#ifndef GEWI_CORE_UI_ELEMENT
#define GEWI_CORE_UI_ELEMENT

#include <vector>

#include <glm/glm.hpp>

#include "style.hpp"

#include "../render/mesh.hpp"
#include "../render/renderer.hpp"

namespace gewi {
    class UI;
    class UILayoutEngine;
    
    class UIElement {
    protected:
        float x, y; //Represent x/y offset from the top left in pixels.
        float width, height; //Represents the width/height in pixels.
        
        glm::mat4 transform_matrix; //Represents the transformation to position and scale this object.
        UI *container; //Holds the UI object that contains this element, which has some global information
        
        UIElement *parent; //Holds the direct predecessor of this element
        std::vector<UIElement *> children; //Holds all children of this element
        
        //Various methods for interaction
        bool contains_point(float x, float y);
        void (*click_callback) (float x, float y); //External click callback
        virtual void click_handler(float x, float y); //Internal click callback
        
        //Used for actually drawing the element
        Mesh *mesh;
        
        //Style information
        Style *style;
    public:
        UIElement();
        virtual ~UIElement();
        
        void add_element(UIElement *elem);
        
        //Simple setters and getters
        void set_pos(float x, float y);
        virtual void set_dims(float width, float height);
        virtual void update_transform_matrix(); //Text may override this, to only use the translation and ignore scaling. 

        
        void render(Renderer *renderer);
        virtual unsigned get_texture() { return 0; }
        
        virtual void set_ui(UI *ui);
        
        void set_style(std::string key, std::string value);
        
        
        void click(float x, float y);
        void install_click_callback(void (*callback) (float x, float y));
            
            
        friend UILayoutEngine;
    };
}
#endif