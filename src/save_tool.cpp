/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
#include "dist/json/json.h"

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"

namespace cge {

void create_json() {
    Json::Value event;
    Json::Value evc(Json::arrayValue);
    evc.append(Json::Value(1));
    evc.append(Json::Value(2));
    evc.append(Json::Value(3));
    
    event["game"]["player"]["name"] = "Keegan";
    event["game"]["player2"]["name"] = "Mario";
    event["game"]["player2"]["health"] = 100;
    
    std::cout << event << std::endl;
}

void create_json(std::vector<Sprite> sprites) {
    
}

void parse_json(std::vector<Sprite> sprites) {
    
}

void save_game(std::vector<Sprite> sprites) {
    cge::create_json(sprites);
}


}
