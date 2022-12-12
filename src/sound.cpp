/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>

#include "src/info.hpp"
#include "src/sound.hpp"

namespace cge {

Sound::Sound() {
    Mix_Init(MIX_INIT_MP3);
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer couldn't init. Err: %s\n", Mix_GetError());
    }
    setVolume(70);
}

Sound::~Sound() {
    for (int s = 0; s < sounds.size(); s++) {
        Mix_FreeChunk(sounds[s]);
        sounds[s] = NULL;
    }
    for (int s = 0; s < music.size(); s++) {
        Mix_FreeMusic(music[s]);
        music[s] = NULL;
    }
}

int Sound::getBackground(int choice) {
    switch (choice) {
        case 0:
            return playMusic(0);
        case 1:
            return playMusic(1);
        default:
            return -1;
    }
}

int Sound::getHit(int choice) {
    switch (choice) {
        case 0:
            return playSound(0);
        case 1:
            return playSound(1);
        default:
            return -1;
    }
}

void Sound::setVolume(int v) {
    volume = (MIX_MAX_VOLUME * v) / 100;
}

int Sound::loadMusic(const char* filename) {
    Mix_Music* m = NULL;
    m = Mix_LoadMUS(filename);
    if (m == NULL) {
        printf("Failed to load music. SDL_MIXER error. SDL_Mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    music.push_back(m);
    return music.size() - 1;
}

int Sound::loadSound(const char* filename) {
    Mix_Chunk* m = NULL;
    m = Mix_LoadWAV(filename);
    if (m == NULL) {
        printf("Failed to load sound. SDL_MIXER error. SDL_Mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    sounds.push_back(m);
    return music.size() - 1;
}

int Sound::playMusic(int m) {
    if (Mix_PlayingMusic() == 0) {
        Mix_Volume(1, volume);
        Mix_PlayMusic(music[m], -1);
    }
    return 0;
}

int Sound::playSound(int s) {
    Mix_Volume(-1, volume);
    Mix_PlayChannel(-1, sounds[s], 0);
    return 0;
}



void init_sdl_mixer() {
    Mix_Init(MIX_INIT_MP3);

}

}

