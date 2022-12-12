
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <string.h>

#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/tree.hpp"
#include "src/water.hpp"
#include "src/capture_zone.hpp"
#include "src/box.hpp"

using namespace std;

namespace cge {

auto resource_path = string(TOSTRING(RESOURCE_DIR));

// Binary Save Methods
string create_sprite_data(Sprite* s) {
    string returnString = "";
    returnString += s->get_name() + "," + to_string( s->get_x_pos()) + "," + to_string(s->get_y_pos()) + "," + to_string(s->get_width()) + ","
        + to_string(s->get_height()) + "," + to_string(s->get_angle()) + "," + (s->get_spinning() ? "true" : "false") + "," 
        + to_string(s->get_screenwidth()) + "," + to_string(s->get_screenheight()) + "," + s->convert_status() + "," + s->convert_type() + "," + s->get_nature_type();
    return returnString;
}

Sprite* parse_data(string sprite) {
    Sprite* s = new Sprite();
    size_t length = sprite.length();
    string array[12];
    char* char_array = new char[length+1];
    strcpy(char_array, sprite.c_str());

    char* token = strtok(char_array, ",");
    int pos = 0;
    while (token != NULL) {
        array[pos] = token;
        token = strtok(NULL, ",");
        pos++;
    }
    for (int i = 0; i < 12; i++) {
        cout << array[i] << ",";
    }
    if (strcmp(array[11].c_str(), "Tree") == 0) {
        s = new Tree(array);
    }
    else if (strcmp(array[11].c_str(), "Water") == 0) {
        s = new Water(array);
    }
    else if (strcmp(array[11].c_str(), "CaptureZone") == 0) {
        s = new CaptureZone(array);
    }
    else {
        s = new Sprite(array);
    }
    return s;
}

Sprite* parse_level(string data) {
    Sprite* s = NULL;
    size_t length = data.length();
    string array[12];
    char* char_array = new char[length + 1];
    strcpy(char_array, data.c_str());

    char* token = strtok(char_array, ",");
    int pos = 0;
    while (token != NULL) {
        array[pos] = token;
        token = strtok(NULL, ",");
        pos++;
    }

    if (strcmp(array[11].c_str(), "Tree") == 0) {
        s = new Tree(array);
    }
    else if (strcmp(array[11].c_str(), "Water") == 0) {
        s = new Water(array);
    }
    else if (strcmp(array[11].c_str(), "CaptureZone") == 0) {
        s = new CaptureZone(array);
    }
    return s;
}

string parse_type(string data) {
    size_t length = data.length();
    string array[9];
    char* char_array = new char[length + 1];
    strcpy(char_array, data.c_str());

    char* token = strtok(char_array, ",");
    int pos = 0;
    while (token != NULL) {
        array[pos] = token;
        token = strtok(NULL, ",");
        pos++;
    }

    return array[8];
}

void save_game(vector<Sprite*> sprites) {
    string game_data = "";
    for (Sprite* s : sprites) {
        string r = create_sprite_data(s);
        game_data += r + "\n";
    }
    string filepath = TOSTRING(resource_path + "save_data/save.json");
    std::remove(filepath.c_str());
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
