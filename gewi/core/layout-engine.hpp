#ifndef GEWI_CORE_UI_LAYOUT_ENGINE
#define GEWI_CORE_UI_LAYOUT_ENGINE
namespace gewi {
    class UIElement;
    
    class UILayoutEngine {
    private:
        void calculate_dimensions(UIElement *root); //Calculate the dimensions of all elements.
        void calculate_layout(UIElement *root); //Calculate the actual positions of all elements.
    public:
        void layout(UIElement *root); //Performs layout calculations on the tree starting at root.
    };
}
#endif