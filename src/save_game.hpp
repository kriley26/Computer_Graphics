/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef save_game_hpp
#define save_game_hpp

#include <chrono>
#include <iostream>
#include <vector>

#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/box.hpp"

using namespace std;

namespace cge {

// Binary Save Data
string create_sprite_data(Sprite* sprite);
Sprite* parse_data(string sprite);
Sprite* parse_level(string data);
string parse_type(string data);
void save_game(vector<Sprite*> sprites);
vector<Sprite*> load_game(string file);

// Json Save Data
string create_box_json(Box* box);
string create_sprite_json(Sprite* sprite);
Sprite* parse_json(string sprite);
void save_json(vector<Sprite*> sprites);
vector<Sprite*> load_json(string file);


}

#endif
