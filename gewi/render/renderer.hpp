#ifndef GEWI_RENDER_RENDERER
#define GEWI_RENDER_RENDERER
namespace gewi {
    class Renderer {
    private: 
        unsigned shader_id;
    public:
        Renderer(const char *vertex_shader, const char *fragment_shader);
        ~Renderer();
        
        void enable();
        
        int transform_location, mode_location;
    };
}

#endif