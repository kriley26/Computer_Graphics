/*
 Developed for JHU 605.668 Computer Gaming Engines
 
 Author: Keegan Riley
 */

#ifndef map_hpp
#define map_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"

using namespace std;

namespace cge {

class Map {
    
private:
    string mapId;
    int width;
    int height;
    
public:
    Map();
    ~Map();
};

Map generateMap();
}

#endif
