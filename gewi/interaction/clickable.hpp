#ifndef GEWI_INTERACTION_CLICKABLE
#define GEWI_INTERACTION_CLICKABLE

class Clickable {
protected:
    void (*click_callback)();
public:
    bool set_click_callback(void (*callback)());
    void click();
}
#endif