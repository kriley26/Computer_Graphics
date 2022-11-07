/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef save_tool_hpp
#define save_tool_hpp

#include <chrono>
#include <thread>
#include <vector>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"

namespace cge {

void create_json();
void save_game(std::vector<Sprite> sprites);
void create_json(std::vector<Sprite> sprites);
void parse_json(std::vector<Sprite> sprites);

}

#endif
