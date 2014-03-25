#ifndef UTILS_FONT_ATLAS
#define UTILS_FONT_ATLAS

#include <string>

typedef struct char_position { //Store a position in texture coordinates
    float x1, y1, x2, y2;
    float width, height;
    float top, left;
} char_position;

class FontAtlas {
private:
    unsigned size;
    std::string file;
    unsigned char *bitmap;
    
    char_position char_positions[128];
    
    unsigned texture_id;
    unsigned bitmap_size;
    void create_texture();
public:
    FontAtlas(std::string &font_file, unsigned font_size);
    ~FontAtlas();
    
    void bind_for_render();
    char_position char_lookup(char c);
    
};

//Functions that will make use of the font atlas cache
FontAtlas *create_font_atlas(std::string &font_file, unsigned font_size);
#endif