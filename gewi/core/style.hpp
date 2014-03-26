#ifndef GEWI_CORE_STYLE
#define GEWI_CORE_STYLE

#include <unordered_map>
#include <string>

namespace gewi {
    class Style {
    private:
        std::unordered_map<std::string, std::string> styles; //Store all style elements as strings, they can be interpreted later
    public:
        Style();
        ~Style();
        void set_style(std::string key, std::string value);
        std::string get_style(std::string key);
    };
}
#endif