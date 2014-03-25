#include <iostream>
#include <fstream>
#include <cmath>

#include <GL/glew.h>
#include <GL/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "font_atlas.hpp"

using namespace std;

//A couple global variables
static FT_Library *library = nullptr;

static void initalize_free_type();

static void initalize_free_type() {
    library = new FT_Library;
    bool error = FT_Init_FreeType(library);
    if (error) {
        cerr << "There was an error initializing freetype\n";
        exit(-1);
    }
}

//Should this be in its own file since I use it a lot?
static void write_to_bitmap(unsigned width, unsigned height, unsigned char *buffer) {
    ofstream stream;
    stream.open("test.bmp");
    unsigned char file[14] = {
        'B','M', // magic
        0,0,0,0, // size in bytes
        0,0, // app data
        0,0, // app data
        40+14,0,0,0 // start of data offset
    };
    unsigned char info[40] = {
        40,0,0,0, // info hd size
        0,0,0,0, // width
        0,0,0,0, // heigth
        1,0, // number color planes
        24,0, // bits per pixel
        0,0,0,0, // compression is none
        0,0,0,0, // image bits size
        0x13,0x0B,0,0, // horz resoluition in pixel / m
        0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0,0,0,0, // #colors in pallete
        0,0,0,0, // #important colors
    };

    int w=width;
    int h=height;

    int padSize  = (4-w%4)%4;
    int sizeData = w*h*3 + h*padSize;
    int sizeAll  = sizeData + sizeof(file) + sizeof(info);

    file[ 2] = (unsigned char)( sizeAll    );
    file[ 3] = (unsigned char)( sizeAll>> 8);
    file[ 4] = (unsigned char)( sizeAll>>16);
    file[ 5] = (unsigned char)( sizeAll>>24);

    info[ 4] = (unsigned char)( w   );
    info[ 5] = (unsigned char)( w>> 8);
    info[ 6] = (unsigned char)( w>>16);
    info[ 7] = (unsigned char)( w>>24);

    info[ 8] = (unsigned char)( h    );
    info[ 9] = (unsigned char)( h>> 8);
    info[10] = (unsigned char)( h>>16);
    info[11] = (unsigned char)( h>>24);

    info[24] = (unsigned char)( sizeData    );
    info[25] = (unsigned char)( sizeData>> 8);
    info[26] = (unsigned char)( sizeData>>16);
    info[27] = (unsigned char)( sizeData>>24);

    stream.write( (char*)file, sizeof(file) );
    stream.write( (char*)info, sizeof(info) );

    unsigned char pad[3] = {0,0,0};

    for ( int y=0; y<h; y++ )
    {
        for ( int x=0; x<w; x++ )
        {
            unsigned char pixel[3];
            pixel[0] = buffer[(y) * width + x];
            pixel[1] = buffer[(y) * width + x];
            pixel[2] = buffer[(y) * width + x];

            stream.write( (char*)pixel, 3 );
        }
        stream.write( (char*)pad, padSize );
    }
    stream.close();
}

//Class methods
FontAtlas::FontAtlas(string &font_file, unsigned font_size) {
    if (library == nullptr) initalize_free_type();
    file = font_file;
    size = font_size;
    
    //Clear out the texture coordinates
    for (int i = 0; i < 128; i++) {
        char_positions[i].x1 = 0;
        char_positions[i].y1 = 0;
        char_positions[i].x2 = 0;
        char_positions[i].y2 = 0;
    }
    
    //Attempt to load up the font file
    FT_Face face;
    bool error = FT_New_Face(*library, file.c_str(), 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        cerr << "Unsupported font file " << font_file << "\n";
        exit(-1);
    }
    else if (error) {
        cerr << "Font file couldn't be opened: " << font_file << "\n";
        exit(-1);
    }
    
    FT_Set_Pixel_Sizes(face, 0, size);
    FT_GlyphSlot g = face->glyph;
    
    //Find the maximum height and total width
    int w = 0, h = 0;
    for(unsigned i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            cerr << "Failed loading character " << char(i) << endl;
            continue;
        }
        w += g->bitmap.width;
        h = max(h, g->bitmap.rows);
    }
    float total_size = w * h;
    float side_length = sqrt(total_size);
    //In theory we could make this tighter...
    bitmap_size = 1;
    while(bitmap_size < side_length)
        bitmap_size <<= 1;
    
    bitmap = new unsigned char[bitmap_size * bitmap_size];
    unsigned char *t = bitmap;
    for (unsigned i = 0; i < bitmap_size * bitmap_size; i++) *t++ = 0;
    
    unsigned x = 0, y = 0;
    for(unsigned i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) continue;
        if(x + g->bitmap.width >= bitmap_size) {
            y+= h;
            x = 0;
        }
        //Copy into the bitmap
        unsigned char *buff = g->bitmap.buffer;
        for (int j = 0; j < g->bitmap.rows; j++) {
            for (int k = 0; k < g->bitmap.width; k++) {
                bitmap[(bitmap_size - (y + j + 1)) * bitmap_size + (x + k)] = *buff++;
            }
        }
        //Store the position of the character
        char_positions[i].x1 = (float) x / bitmap_size; 
        char_positions[i].y1 = (float) y / bitmap_size;
        char_positions[i].x2 = (x + (float) g->bitmap.width) / bitmap_size; 
        char_positions[i].y2 = (y + (float) g->bitmap.rows) / bitmap_size;
       
        x += g->bitmap.width;
    }
    
    //Write it out to an image file for debugging.
    write_to_bitmap(bitmap_size, bitmap_size, bitmap);
    
    //Create the textures
    texture_id = 0;
    create_texture();
}
    
   
    
FontAtlas::~FontAtlas() {
    delete[] bitmap;
}

void FontAtlas::bind_for_render() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

char_position FontAtlas::char_lookup(char c) {
    return char_positions[(int) c];
}
void FontAtlas::create_texture() {
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap_size, bitmap_size, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
}

FontAtlas *create_font_atlas(string &font_file, unsigned font_size) {
    FontAtlas *atlas;
    //Check the cache
    
    //Not in the cache? Make a new font atlas
    atlas = new FontAtlas(font_file, font_size);
    return atlas;
}