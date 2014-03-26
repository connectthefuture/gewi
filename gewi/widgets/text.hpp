#ifndef GEWI_WIDGETS_TEXT
#define GEWI_WIDGETS_TEXT

#include <string>

#include "../../utils/font_atlas.hpp"
#include "../core/ui-object.hpp"

namespace gewi {
    class Text : public UIObject {
    private:
        FontAtlas *atlas;
    public:
        Text(FontAtlas *atlas, std::string text);
        ~Text();
        void render(Renderer *renderer);
    };
}
#endif