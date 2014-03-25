#ifndef GEWI_WIDGETS_BUTTON
#define GEWI_WIDGETS_BUTTON

#include "../core/ui-object.hpp"
#include "../interaction/clickable.hpp"
namespace gewi {
    class Button : public Clickable {
    private:
    public:
        Button();
        ~Button();
        void render();
        
        void change_position_or_size();
    };
}
#endif