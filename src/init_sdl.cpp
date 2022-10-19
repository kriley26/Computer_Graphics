/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include "src/init_sdl.hpp"

#include <cstring>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace cge
{

void init_sdl()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

void create_sdl_components(SDLInfo &sdl_info, int window_width, int window_height)
{
	constexpr int WINDOW_FLAGS = 0;

	sdl_info.window = SDL_CreateWindow("Class 605.688: Computer Gaming Engines", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, WINDOW_FLAGS);
	
	if( sdl_info.window == nullptr ) 
	{
		std::cout << "Error initializing SDL Window" << SDL_GetError() << std::endl;
		exit(1);
	}

	constexpr uint32_t RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;
	constexpr int FIRST_SUPPORTED_RENDERING_DRIVER = -1;;

	sdl_info.renderer = SDL_CreateRenderer(sdl_info.window, FIRST_SUPPORTED_RENDERING_DRIVER, RENDERER_FLAGS);

	if( sdl_info.renderer == nullptr ) 
	{
		std::cout << "Error initializing SDL Renderer" << SDL_GetError() << std::endl;
		exit(1);
	}
}

void destroy_sdl_components(SDLInfo &sdl_info)
{
	SDL_DestroyRenderer(sdl_info.renderer);
	SDL_DestroyWindow(sdl_info.window);
	SDL_Quit();
}

} // namespace cge
