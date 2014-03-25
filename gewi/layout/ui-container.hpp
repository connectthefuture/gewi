#ifndef GEWI_LAYOUT_CONTAINER
#define GEWI_LAYOUT_CONTAINER

#include <vector> 

#include "../core/ui-object.hpp"

namespace gewi {
    class UIContainer : public UIObject {
    protected:
        UIContainer *parent;
        std::vector<UIObject *> children; //Can have arbitrary children
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