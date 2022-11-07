/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef sound_hpp
#define sound_hpp

#include <chrono>
#include <thread>
#include <vector>

#include "src/info.hpp"

namespace cge {

void init_sdl_mixer();

class Sound {
private:
    std::string background_one;
    std::string background_two;
    std::string wall_hit;
    std::string character_hit;
    
public:
    Sound();
    ~Sound();
    void loadFiles(int choice, std::string f);
    void playFile(const char* filepath);
    std::string getBackground(int choice);
    std::string getHit(int choice);
};
}

#endif
