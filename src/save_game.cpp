
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/box.hpp"

namespace cge {


auto resource_path = std::string(TOSTRING(RESOURCE_DIR));

std::string create_box_data(Box* box) {
    std::string returnString = "";
    returnString += std::to_string(box->getMinX()) + "," + std::to_string(box->getMaxX())+ "," + std::to_string(box->getMinY()) + "," + std::to_string(box->getMaxY());
    return returnString;
}

std::string create_sprite_data(Sprite* s) {
    std::string returnString = "";
    returnString += s->get_name() + "," + std::to_string( s->get_x_pos()) + "," + std::to_string(s->get_y_pos()) + "," + std::to_string(s->get_angle()) + "," + (s->get_spinning() ? "true" : "false") + "," + std::to_string(s->get_screenwidth()) + "," + std::to_string(s->get_screenheight()) + "," + create_box_data(s->getOutline());
    return returnString;
}

Sprite* parse_data(std::string sprite) {
    Sprite* s = new Sprite();
    long length = sprite.length();
    std::string array[11];
    char char_array[length+1];
    strcpy(char_array, sprite.c_str());

    char* token = strtok(char_array, ",");
    int pos = 0;
    while (token != NULL) {
        array[pos] = token;
        token = strtok(NULL, ",");
        pos++;
    }
    for (int i = 0; i < 11; i++) {
        cout << array[i] << ",";
    }
    s = new Sprite(array);
    return s;
}

void save_game(std::vector<Sprite*> sprites) {
    std::string game_data = "";
    for (Sprite* s : sprites) {
        std::string r = create_sprite_data(s);
        game_data += r + "\n";
    }
    
    ofstream main_save(resource_path + "save_data/save.json");
    main_save << game_data;
    main_save.close();
}

std::vector<Sprite*> load_game(std::string file) {
    std::vector vec = vector<Sprite*>();
    return vec;
}

}
