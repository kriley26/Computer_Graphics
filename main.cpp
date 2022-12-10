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
#include <SDL2/SDL_mixer.h>

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
#include "src/map.hpp"
#include "src/sprite_sheet.hpp"
#include "src/menu.hpp"

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

    cge::Map *m;
    cge::Map map = cge::generateMap();
    cge::Map map2 = cge::generateMap();
    
    cout << "M equals Map 1" << endl;
    m = &map;
    cout << "Addr M: " << &m << endl;
    cout << "M: " << m << endl;
    cout << "Map: " << &map << endl;
    cout << "Map2: " << &map2 << endl;
    
    cout << "M equals Map 2" << endl;
    m = &map2;
    cout << "Addr M: " << &m << endl;
    cout << "M: " << m << endl;
    cout << "Map: " << &map << endl;
    cout << "Map2: " << &map2 << endl;
    
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
	auto brad_texture_path = resource_path + string("images/thebrad.png");
	auto chad_texture_path = resource_path + string("images/thechad.png");
	auto man_texture_path = resource_path + string("images/theman.png");
    
    // Audio File Paths
    auto background_one_path = resource_path + std::string("audio/game_select.mp3");
    auto backgroung_two_path = resource_path + std::string("audio/sunny_side_up.mp3");
    auto wall_hit_path = resource_path + std::string("audio/mk64_boo_laugh.wav");
    auto character_hit_path = resource_path + std::string("audio/mk64_bowser02.wav");

	// Sprite Sheets
	cge::SpriteSheet* chad_sheet = cge::import_spritesheet(chad_texture_path);
	cge::SpriteSheet* brad_sheet = cge::import_spritesheet(brad_texture_path);
	cge::SpriteSheet* man_sheet = cge::import_spritesheet(man_texture_path);
    
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
	cge::Sprite* s1 = new cge::Sprite();
    cge::Sprite* s2 = new cge::Sprite();
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
        s1 = new cge::Sprite(100, 500, sdl_info, mario_text, 75, 125, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
        s2 = new cge::Sprite(300, 500, sdl_info, mario_text, 75, 125, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
        s3 = new cge::Sprite(500, 500, sdl_info, man_sheet, 75, 125, SCREEN_WIDTH, SCREEN_HEIGHT, &sound);
    }
	cge::Player player(std::string(TOSTRING("Player 1")), s3);
	std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nStart time: " << start_time << "\n";

	s1->set_Name("Left Mario");
	s2->set_Name("Right Mario");

	std::vector<cge::Sprite*> npcSprites;
	std::vector<cge::Sprite*> allSprites;
	//npcSprites.push_back(s1)/*;
	//npcSprites.push_back(s2);   
	//allSprites.push_back(s1);
	//allSprites.push_back(s2);*/
	allSprites.push_back(s3);
    
    sound.playFile(sound.getBackground(0).c_str());
    int frameNum = 0;
    
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
				case cge::EventType::UP_DOWN:
					player.moveUp();
					player.getCharacter()->update_sprite();
                    frameNum = player.getCharacter()->update_animation(frameNum);
					break;
				case cge::EventType::DOWN_DOWN:
					player.moveDown();
					player.getCharacter()->update_sprite();
                    frameNum = player.getCharacter()->update_animation(frameNum);
					break;
				case cge::EventType::LEFT_DOWN:
					player.moveLeft();
					player.getCharacter()->update_sprite();
                    frameNum = player.getCharacter()->update_animation(frameNum);
					break;
				case cge::EventType::RIGHT_DOWN:
					player.moveRight();
					player.getCharacter()->update_sprite();
                    frameNum = player.getCharacter()->update_animation(frameNum);
					break;
				case cge::EventType::DOWN_UP:
				case cge::EventType::UP_UP:
				case cge::EventType::LEFT_UP:
				case cge::EventType::RIGHT_UP:
					player.stopMovement();
                    frameNum = 0;
					break;
				default:
					break;
			}
		}

		if (get_time(since_update, updateSpeed)) {
			for (cge::Sprite* s : npcSprites) {
				s->detectCollision(player.getCharacter());
				s->update_sprite();
			}
			updateCount++;
			since_update = std::chrono::system_clock::now();
		}

		if (get_time(since_draw, drawSpeed)) {
			SDL_RenderClear(sdl_info.renderer);
			for (cge::Sprite* s : allSprites) {
				s->draw_sprite();
			}
			drawCount++;
			since_draw = std::chrono::system_clock::now();
			SDL_RenderPresent(sdl_info.renderer);

		}

		if (get_time(since_change_vec, changeVectorSpeed)) {
			for (cge::Sprite* sprite : npcSprites) {
				sprite->updateVector();
			}
			since_change_vec = std::chrono::system_clock::now();
		}
	}

    cge::save_game(allSprites);
	std::cout << "\nUpdate Count: " << updateCount << "\nDrawCount: " << drawCount;
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nEnd time: " << end_time << "\n";

	//cge::destroy_texture(box_texture);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
