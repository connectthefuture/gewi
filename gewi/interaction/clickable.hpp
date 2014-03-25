#ifndef GEWI_INTERACTION_CLICKABLE
#define GEWI_INTERACTION_CLICKABLE
namespace gewi {
    class Clickable {
    protected:
        void (*click_callback)();
    public:
        void set_click_callback(void (*callback)());
        void click();
    };
}
#endif