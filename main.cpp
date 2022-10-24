/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>

#include "src/image.hpp"
#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"
#include "src/sprite.hpp"
#include "src/vector.hpp"
#include "src/player.hpp"
#include "src/texture.hpp"

std::chrono::system_clock::time_point since_update;
std::chrono::system_clock::time_point since_draw;
std::chrono::system_clock::time_point since_change_vec;

void sleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void init_time() {
	since_update = std::chrono::system_clock::now();
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

	cge::SDLInfo sdl_info;

	constexpr int SCREEN_WIDTH = 1200;
	constexpr int SCREEN_HEIGHT = 900;
	cge::create_sdl_components(sdl_info, SCREEN_WIDTH, SCREEN_HEIGHT);

	cge::init_sdl_image();

	SDL_SetRenderDrawColor(sdl_info.renderer, 5, 85, 85, 255);

	auto resource_path = std::string(TOSTRING(RESOURCE_DIR));

	auto box_texture_path = resource_path + std::string("images/box.png");
	auto mario_texture_path_1 = resource_path + std::string("images/mario.png");
	auto mario_texture_path_2 = resource_path + std::string("images/mario_run.png");
	auto mario_texture_jump = resource_path + std::string("images/mario_jump.png");

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
	cge::Sprite s1(100, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT);
	cge::Sprite s2(300, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT);
	cge::Sprite s3(500, 500, sdl_info, mario_text, 150, 200, SCREEN_WIDTH, SCREEN_HEIGHT);
    
	cge::Player player(std::string(TOSTRING("Player 1")), &s3);
	std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nStart time: " << start_time << "\n";

	std::vector<cge::Sprite*>  sprites;
	sprites.push_back(&s1);
	sprites.push_back(&s2);
	sprites.push_back(&s3);
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
            s1.detectCollision(s3);
            s2.detectCollision(s3);
            
			s1.update_sprite();
			s2.update_sprite();
			updateCount++;
			since_update = std::chrono::system_clock::now();
		}

		if (get_time(since_draw, drawSpeed)) {
			SDL_RenderClear(sdl_info.renderer);
			s1.draw_sprite();
			s2.draw_sprite();
			s3.draw_sprite();
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

	std::cout << "\nUpdate Count: " << updateCount << "\nDrawCount: " << drawCount;
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nEnd time: " << end_time << "\n";

	//cge::destroy_texture(box_texture);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
