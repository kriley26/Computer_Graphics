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
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					event_info.events[num_events++] = EventType::QUIT;
					break;
				case SDLK_SPACE:
					event_info.events[num_events++] = EventType::INTERACT;
					break;
				case SDLK_m:
					event_info.events[num_events++] = EventType::TOGGLE_MUSIC;
					break;
				case SDLK_w:
				case SDLK_UP:
					event_info.events[num_events++] = EventType::UP_DOWN;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					event_info.events[num_events++] = EventType::LEFT_DOWN;
					break;
				case SDLK_s:
				case SDLK_DOWN:
					event_info.events[num_events++] = EventType::DOWN_DOWN;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					event_info.events[num_events++] = EventType::RIGHT_DOWN;
					break;
				case SDLK_p:
					event_info.events[num_events++] = EventType::PAUSE;
					break;
				case SDLK_b:
					event_info.events[num_events++] = EventType::PLAY_SOUND;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_w:
				case SDLK_UP:
					event_info.events[num_events++] = EventType::UP_UP;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					event_info.events[num_events++] = EventType::LEFT_UP;
					break;
				case SDLK_s:
				case SDLK_DOWN:
					event_info.events[num_events++] = EventType::DOWN_UP;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					event_info.events[num_events++] = EventType::RIGHT_UP;
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




