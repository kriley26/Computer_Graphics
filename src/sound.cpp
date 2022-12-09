/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#include "src/info.hpp"
#include "src/sound.hpp"

namespace cge {

void init_sdl_mixer() {
    Mix_Init(MIX_INIT_MP3);
}

Sound::Sound() {
    
}

Sound::~Sound() {
    
}


void Sound::loadFiles(int choice, std::string *f) {
    switch (choice) {
        case 0:
            background_one = f;
            break;
        case 1:
            background_two = f;
            break;
        case 2:
            wall_hit = f;
            break;
        case 3:
            character_hit = f;
            break;
        default:
            break;
    }
}

void Sound::playFile(const char* filepath) {
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS(filepath);
    Mix_PlayMusic(music, 1);
//    Mix_PlayChannel(1, <#Mix_Chunk *chunk#>, <#int loops#>)
}

std::string Sound::getBackground(int choice) {
    switch (choice) {
        case 0:
            return *background_one;
        case 1:
            return *background_two;
        default:
            return "";
    }
}

std::string Sound::getHit(int choice) {
    switch (choice) {
        case 0:
            return *wall_hit;
        case 1:
            return *character_hit;
        default:
            return "";
    }
}

}

