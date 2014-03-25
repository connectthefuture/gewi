#ifndef GEWI_CORE_UIOBJECT
#define GEWI_CORE_UIOBJECT

#include "../render/mesh.hpp"

namespace gewi {
    class UIObject {
    protected:
        float width, height;
        float x, y;
        Mesh *mesh;
    public:
        //Every UIobject must be renderable.
        UIObject();
        virtual ~UIObject() { }
        virtual void render() = 0;
        virtual void change_position_or_size() { }
        
        
        
        //Simple setters and getters
        void set_xy(float x, float y);
        void set_dim(float width, float height);
        void get_xy(float &x, float &y);
        void get_dim(float &width, float &height);
    };
}
#endif