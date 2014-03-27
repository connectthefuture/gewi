#include <iostream>

#include "style.hpp"

using namespace gewi;

Style::Style() { }

Style::~Style() { }

void Style::set_style(std::string key, std::string value) {
    styles[key] = value;
}

std::string Style::get_style(std::string key) {
    try {
        return styles.at(key);
    } catch (const std::out_of_range& oor) { }
    return std::string("");
}