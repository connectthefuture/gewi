#ifndef GEWI_LAYOUT_CONTAINER
#define GEWI_LAYOUT_CONTAINER
class UIContainer {
protected:
    float x, y; //Position relative to the parent
    unsigned width, height; //In OpenGL coordinates (e.g. 2x2 will fill the entire parent)
public:
    
};
#endif