#ifndef GEWI_RENDER_MESH
#define GEWI_RENDER_MESH

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
namespace gewi {
    //This is a simple 2D mesh with only vertex data
    class Mesh {
    private:
        GLuint vao_id, vbuf_id, texbuf_id;
        GLenum prim_type;
        unsigned num_vertices;
    public:
        Mesh(GLenum prim_type);
        void load_vertex_data(unsigned num_vertices, glm::vec2 *verts);
        void load_tex_coords(unsigned num_vertices, glm::vec2 *tex_coords);
        void update_vertex_data(unsigned num_vertices, glm::vec2 *verts);
        void render();
    };
}
#endif