/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include <chrono>
#include <iostream>
#include <thread>

#include <SDL2/SDL.h>

#include "src/image.hpp"
#include "src/info.hpp"
#include "src/init_sdl.hpp"
#include "src/input.hpp"
#include "src/preprocessor.h"

void sleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main(int argc, char *argv[])
{	
	cge::init_sdl();

	cge::SDLInfo sdl_info;

	constexpr int SCREEN_WIDTH = 1200;
	constexpr int SCREEN_HEIGHT = 900;
	cge::create_sdl_components(sdl_info, SCREEN_WIDTH, SCREEN_HEIGHT);

	cge::init_sdl_image();

	SDL_SetRenderDrawColor(sdl_info.renderer, 64, 64, 64, 255);

	auto resource_path = std::string(TOSTRING(RESOURCE_DIR));

	auto box_texture_path = resource_path + std::string("images/box.png");
	auto box_texture = create_texture(sdl_info, box_texture_path.c_str());

	cge::SDLTextureOptions box_opts;
	box_opts.width = 100;
	box_opts.height = 100;
	box_opts.blend_mode = SDL_BLENDMODE_BLEND;
	box_opts.blend_alpha = 128;
	box_opts.color_mod[0] = 128;
	box_opts.color_mod[1] = 0;
	box_opts.color_mod[2] = 0;

	bool run_game = true;
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
				default:
					break;
			}
		}

		SDL_RenderClear(sdl_info.renderer);

		cge::render_texture(sdl_info, box_texture, 100, 100, box_opts);

        SDL_RenderPresent(sdl_info.renderer);
		sleep(16);
	}

	cge::destroy_texture(box_texture);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
