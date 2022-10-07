/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include "src/input.hpp"

#include <SDL2/SDL.h>

namespace cge
{

SDLEventInfo get_current_events()
{
	SDLEventInfo event_info;
	uint8_t num_events = 0;

	SDL_Event e;
	while (SDL_PollEvent(&e) && num_events < SDLEventInfo::MAX_EVENTS)
	{
		switch(e.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_QUIT:
				event_info.events[num_events++] = EventType::QUIT;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE: 
						event_info.events[num_events++] = EventType::QUIT;
						break;
					case SDLK_SPACE: 
						event_info.events[num_events++] = EventType::PLAY_SOUND;
						break;
					case SDLK_m: 
						event_info.events[num_events++] = EventType::TOGGLE_MUSIC;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	event_info.num_events = num_events;

	return event_info;
}

} // namespace cge




