/*
 Developed for JHU 605.668 Computer Gaming Engines
 
 Author: Keegan Riley
 */

#include <chrono>
#include <iostream>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/map.hpp"

using namespace std;

namespace cge {
    
Map::Map() {
    mapId = "base";
    width = 0;
    height = 0;
}

Map::~Map() {
    cout << "Map deconstruct" << endl;
}

Map generateMap() {
    cge::Map m = cge::Map();
    return m;
};
}
