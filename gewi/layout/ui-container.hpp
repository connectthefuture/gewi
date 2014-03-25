#ifndef GEWI_LAYOUT_CONTAINER
#define GEWI_LAYOUT_CONTAINER

#include <vector> 

#include "../core/ui-object.hpp"
#include "../interaction/clickable.hpp"

namespace gewi {
    class UIContainer : public Clickable {
    protected:
        UIContainer *parent;
        std::vector<UIObject *> children; //Can have arbitrary children
        void internal_click_callback(float x, float y);
    public:
        void render();
        UIContainer();
        ~UIContainer();
        
        //Simple get and set methods for the parents
        UIContainer *get_parent();
        void set_parent(UIContainer *parent);
        
        void add_ui_object(UIObject *obj);
    };
}
#endif