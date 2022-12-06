/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

#include "src/image.hpp"
#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/vector.hpp"
#include "src/player.hpp"
#include "src/texture.hpp"
#include "src/sound.hpp"
#include "src/save_game.hpp"

using namespace std;

chrono::system_clock::time_point since_update;
chrono::system_clock::time_point since_draw;
chrono::system_clock::time_point since_change_vec;

void sleep(int milliseconds)
{
	this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void init_time() {
	since_update = chrono::system_clock::now();
	since_draw = std::chrono::system_clock::now();
	since_change_vec = std::chrono::system_clock::now();
}

bool get_time(std::chrono::system_clock::time_point time, double limit) {

	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_time =  now - time;

	if (elapsed_time.count() > limit) {
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char *argv[])
{	
	cge::init_sdl();
    
    //cge::create_json();

	cge::SDLInfo sdl_info;

	constexpr int SCREEN_WIDTH = 1200;
	constexpr int SCREEN_HEIGHT = 900;
	cge::create_sdl_components(sdl_info, SCREEN_WIDTH, SCREEN_HEIGHT);

	cge::init_sdl_image();
    cge::init_sdl_mixer();

	SDL_SetRenderDrawColor(sdl_info.renderer, 5, 85, 85, 255);

	auto resource_path = std::string(TOSTRING(RESOURCE_DIR));

    // Image File Paths
	auto box_texture_path = resource_path + std::string("images/box.png");
	auto mario_texture_path_1 = resource_path + std::string("images/mario.png");
	auto mario_texture_path_2 = resource_path + std::string("images/mario_run.png");
	auto mario_texture_jump = resource_path + std::string("images/mario_jump.png");
    
    // Audio File Paths
    auto background_one_path = resource_path + std::string("audio/game_select.mp3");
    auto backgroung_two_path = resource_path + std::string("audio/sunny_side_up.mp3");
    auto wall_hit_path = resource_path + std::string("audio/mk64_boo_laugh.wav");
    auto character_hit_path = resource_path + std::string("audio/mk64_bowser02.wav");
    
    cge::Sound sound;
    sound.loadFiles(0, &background_one_path);
    sound.loadFiles(1, &backgroung_two_path);
    sound.loadFiles(2, &wall_hit_path);
    sound.loadFiles(3, &character_hit_path);

	std::vector<std::string*> mario_movement;
	mario_movement.push_back(&mario_texture_path_1);
	mario_movement.push_back(&mario_texture_path_2);

	cge::Texture mario_text;
	mario_text.add_walk(mario_movement);
	mario_text.add_jump(mario_texture_jump);

	cge::SDLTextureOptions box_opts;
	box_opts.width = 250;
	box_opts.height = 250;
	box_opts.color_mod[0] = 128;
	box_opts.color_mod[1] = 50;
	box_opts.color_mod[2] = 75;

	bool run_game = true;
	double updateSpeed = .075;
	double drawSpeed = .016667;
	double changeVectorSpeed = 5;
	int updateCount = 0;
	int drawCount = 0;
    std::string jsonFile = "";
    if (FILE *file = fopen((resource_path + "save_data/save.json").c_str(), "r")) {

    }
	cge::Sprite* s1 = NULL;
    cge::Sprite* s2 = NULL;
    cge::Sprite* s3 = NULL;
    if (FILE *file = fopen((resource_path + "save_data/save.json").c_str(), "r")) {
        std::cout << "File present" << endl;
        std::string text;
        ifstream myFile(resource_path + "save_data/save.json");

        while (getline(myFile, text)) {
            if (s1 == NULL) {
                s1 = cge::parse_data(text);
                s1->set_SDLInfo(sdl_info);
                s1->set_Texture(mario_text);
                s1->set_screenWidth(SCREEN_WIDTH);
                s1->set_screenHeight(SCREEN_HEIGHT);
                s1->set_Sound(&sound);
            } else if (s2 == NULL) {
                s2 = cge::parse_data(text);
                s2->set_SDLInfo(sdl_info);
                s2->set_Texture(mario_text);
                s2->set_screenWidth(SCREEN_WIDTH);
                s2->set_screenHeight(SCREEN_HEIGHT);
                s2->set_Sound(&sound);
            } else {
                s3 = cge::parse_data(text);
                s3->set_SDLInfo(sdl_info);
                s3->set_Texture(mario_text);
                s3->set_screenWidth(SCREEN_WIDTH);
                s3->set_screenHeight(SCREEN_HEIGHT);
                s3->set_Sound(&sound);
            }

        }

    } else {
        s1 = new cge::Sprite(100, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
        s2 = new cge::Sprite(300, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
        s3 = new cge::Sprite(500, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
    }
	cge::Player player(std::string(TOSTRING("Player 1")), s3);
	std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nStart time: " << start_time << "\n";

	std::vector<cge::Sprite*>  sprites;
	sprites.push_back(s1);
	sprites.push_back(s2);
	sprites.push_back(s3);
    
    sound.playFile(sound.getBackground(0).c_str());
    
	while (run_game)
	{
		auto curr_events = cge::get_current_events();
		for( uint8_t i = 0; i < curr_events.num_events; ++i )
		{
			switch(curr_events.events[i])
			{
				case cge::EventType::QUIT: // 'esc' or close window
					run_game = false;
					break;
				case cge::EventType::UP:
					player.moveUp();
					player.getCharacter()->update_sprite();
					break;
				case cge::EventType::DOWN:
					player.moveDown();
					player.getCharacter()->update_sprite();
					break;
				case cge::EventType::LEFT:
					player.moveLeft();
					player.getCharacter()->update_sprite();
					break;
				case cge::EventType::RIGHT:
					player.moveRight();
					player.getCharacter()->update_sprite();
					break;
				default:
					break;
			}
		}

		if (get_time(since_update, updateSpeed)) {
            s1->detectCollision(s3);
            s2->detectCollision(s3);
            
			s1->update_sprite();
			s2->update_sprite();
			updateCount++;
			since_update = std::chrono::system_clock::now();
		}

		if (get_time(since_draw, drawSpeed)) {
			SDL_RenderClear(sdl_info.renderer);
			s1->draw_sprite();
			s2->draw_sprite();
			s3->draw_sprite();
			drawCount++;
			since_draw = std::chrono::system_clock::now();
			SDL_RenderPresent(sdl_info.renderer);
		}

		if (get_time(since_change_vec, changeVectorSpeed)) {
			for (int i = 0; i < 3; i++) {
				sprites[i]->updateVector();
			}
			since_change_vec = std::chrono::system_clock::now();
		}
	}

    cge::save_game(sprites);
	std::cout << "\nUpdate Count: " << updateCount << "\nDrawCount: " << drawCount;
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nEnd time: " << end_time << "\n";

	//cge::destroy_texture(box_texture);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
