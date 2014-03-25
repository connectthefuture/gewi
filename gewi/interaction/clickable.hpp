#ifndef GEWI_INTERACTION_CLICKABLE
#define GEWI_INTERACTION_CLICKABLE

#include "../core/ui-object.hpp"
namespace gewi {
    class Clickable : public UIObject{
    protected:
        void (*click_callback)();
        virtual void internal_click_callback(float x, float y) { }
    public:
        Clickable();
        virtual ~Clickable();
        
        void set_click_callback(void (*callback)());
        
        void click(float x, float y);
        
        bool is_clickable() { return true; }
        
        virtual void render() { }
    };
}
#endif