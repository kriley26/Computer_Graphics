
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

using namespace std;

namespace cge {

auto resource_path = string(TOSTRING(RESOURCE_DIR));

// Binary Save Methods

string create_box_data(Box* box) {
    string returnString = "";
    returnString += std::to_string(box->getMinX()) + "," + to_string(box->getMaxX())+ "," + to_string(box->getMinY()) + "," + to_string(box->getMaxY());
    return returnString;
}

string create_sprite_data(Sprite* s) {
    string returnString = "";
    returnString += s->get_name() + "," + to_string( s->get_x_pos()) + "," + to_string(s->get_y_pos()) + "," + to_string(s->get_angle()) + "," + (s->get_spinning() ? "true" : "false") + "," + to_string(s->get_screenwidth()) + "," + to_string(s->get_screenheight()) + "," + create_box_data(s->getOutline());
    return returnString;
}

Sprite* parse_data(string sprite) {
    Sprite* s = new Sprite();
    size_t length = sprite.length();
    string array[11];
    char* char_array = new char[length+1];
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

void save_game(vector<Sprite*> sprites) {
    string game_data = "";
    for (Sprite* s : sprites) {
        string r = create_sprite_data(s);
        game_data += r + "\n";
    }
    
    ofstream main_save(resource_path + "save_data/save.json");
    main_save << game_data;
    main_save.close();
}

vector<Sprite*> load_game(string file) {
    vector vec = vector<Sprite*>();
    return vec;
}

// JSON Save Data


}
