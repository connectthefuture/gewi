#ifndef GEWI_CORE_UIOBJECT
#define GEWI_CORE_UIOBJECT

#include <vector>
#include <glm/glm.hpp>

#include "style.hpp"

#include "../render/mesh.hpp"
#include "../render/renderer.hpp"

namespace gewi {
    class UIObject {
    private:
        //Store the representation in screen space
        float x, y;
        float width, height;
        
        glm::mat4 transform_matrix; //Combination of translation and scale.
        void update_transform();
       
        //Members for dealing with the tree
        UIObject *parent;
        std::vector<UIObject *> children;
        
        //Style elements
        Style *style;
        void apply_style();
        
        //Attributes for interaction
        bool selected;
        
        //Callbacks
        void (*click_callback)(float x, float y); //X and Y in root coordinates
        
    protected:
        Mesh *mesh;
    public:
        //Every UIobject must be renderable.
        UIObject();
        virtual ~UIObject();
        virtual void render(Renderer *renderer);
        
        //Methods for dealing with the tree
        void add_child(UIObject *child);
        void set_parent(UIObject *parent);
        UIObject *get_parent();
        
        //Methods for changing style
        void set_style(std::string key, std::string value);
        std::string get_style(std::string key);
        
        //Methods for interaction
        bool contains_point(float x, float y);
        void click(float x, float y);
        
        void set_click_callback(void (*callback)(float, float));
    };
}
#endif