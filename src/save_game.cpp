
#include <chrono>
#include <thread>
#include <string>

#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/box.hpp"

namespace cge {

std::string create_box_data(Box* box) {
    std::string returnString = "";
    return returnString;
}

std::string create_sprite_data(Sprite* sprite) {
    std::string returnString = "";
    return returnString;
}

Box parse_box_data(std::string box) {
    Box b = Box();
    return b;
}

Sprite parse_sprite_data(std::string sprite) {
    Sprite s = Sprite();
    return s;
}

void save_game(std::vector<Sprite*> sprites) {
    for (Sprite* s : sprites) {
        std::string r = create_sprite_data(s);
    }
}

std::vector<Sprite*> load_game(std::string file) {
    std::vector vec = vector<Sprite*>();
    return vec;
}

}
