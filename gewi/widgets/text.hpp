#ifndef GEWI_WIDGETS_TEXT
#define GEWI_WIDGETS_TEXT

#include <string>

#include "../../utils/font_atlas.hpp"
#include "../core/ui-object.hpp"

namespace gewi {
    class Text : public UIObject {
    private:
        FontAtlas *atlas;
        void add_char(char c, float &base_x, float base_y, glm::vec2 *vert, glm::vec2 *tex);
    public:
        Text(FontAtlas *atlas, std::string text);
        ~Text();
        void render(Renderer *renderer);
    };
}
#endif