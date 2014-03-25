#ifndef GEWI_CORE_UIOBJECT
#define GEWI_CORE_UIOBJECT
namespace gewi {
    class UIObject {
    protected:
        float width, height;
        float x, y;
    public:
        //Every UIobject must be renderable.
        UIObject() { }
        virtual ~UIObject() { }
        virtual void render() = 0;
        
        //Simple setters and getters
        void set_xy(float x, float y);
        void set_dim(float width, float height);
        void get_xy(float &x, float &y);
        void get_dim(float &width, float &height);
    };
}
#endif