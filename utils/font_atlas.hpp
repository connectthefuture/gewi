#ifndef UTILS_FONT_ATLAS
#define UTILS_FONT_ATLAS

class FontAtlas {
private:
    unsigned size;
    const char *font_file;
public:
    FontAtlas();
    ~FontAtlas();
    
};

//Functions that will make use of the font atlas cache
FontAtlas *create_font_atlas(char *font_file, unsigned font_size);
#endif