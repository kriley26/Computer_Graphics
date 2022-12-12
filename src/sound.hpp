/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef sound_hpp
#define sound_hpp

#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>

#include "src/info.hpp"


namespace cge {

void init_sdl_mixer();

class Sound {
private:
    std::string* background_one;
    std::string* background_two;
    std::string* wall_hit;
    std::string* character_hit;
    std::vector<Mix_Chunk*> sounds;
    std::vector<Mix_Music*> music;
    int volume;
    
public:
    Sound();
    ~Sound();
    void loadFiles(int choice, std::string *f);
    void playFile(const char* filepath);
    int getBackground(int choice);
    int getHit(int choice);

    void setVolume(int v);
    int loadMusic(const char* filename);
    int loadSound(const char* filename);

    int playMusic(int m);
    int playSound(int s);
};
}

#endif
