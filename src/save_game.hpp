/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef save_game_hpp
#define save_game_hpp

#include <chrono>
#include <thread>
#include <vector>

#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/box.hpp"

namespace cge {

std::string create_box_data(Box* box);
std::string create_sprite_data(Sprite* sprite);
Box parse_box_data();
Sprite parse_sprite_data();
void save_game(std::vector<Sprite*> sprites);
std::vector<Sprite*> load_game(std::string file);

}

#endif
