#ifndef GEWI_WIDGETS_BUTTON
#define GEWI_WIDGETS_BUTTON

#include "../core/ui-object.hpp"
#include "../interaction/clickable.hpp"
namespace gewi {
    class Button : public UIObject, public Clickable {
    private:
    public:
        void render() { }
    };
}
#endif