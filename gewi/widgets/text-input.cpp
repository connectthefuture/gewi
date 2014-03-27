#include <iostream>
#include "text-input.hpp"

using namespace gewi;

TextInput::TextInput(FontAtlas *atlas) {
    this->atlas = atlas;
    set_text("");
}
TextInput::~TextInput() {
    delete mesh;
}
        
void TextInput::key_press_handler(int key, int mods) {
    if (key == 259 && text.size() > 0) //backspace
        text.pop_back();
    else if (key < 128) {
        if (mods & 0x1) //Shift key from GLFW
            text += key;
        else
            text += tolower(key);
    }
    set_text(text);
}