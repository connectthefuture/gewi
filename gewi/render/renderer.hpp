#ifndef GEWI_RENDER_RENDERER
#define GEWI_RENDER_RENDERER
namespace gewi {
    class Renderer {
    private:
        unsigned shader_id;
        
    public:
        Renderer();
        ~Renderer();
        
        unsigned transform_loc;
    };
}

#endif