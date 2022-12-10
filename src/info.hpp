/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#ifndef info_hpp
#define info_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace cge
{

struct SDLInfo
{
	SDL_Window *window;
	SDL_Renderer *renderer;
};

enum class EventType
{
	PLAY_SOUND,
	TOGGLE_MUSIC,
	QUIT,
	UP_UP, 
	UP_DOWN,
	DOWN_UP,
	DOWN_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
	LEFT_UP,
	LEFT_DOWN
};

enum DIRECTION_FACING : int {
	RIGHT,
	LEFT,
	DOWN,
	UP
};

enum class ACTIVITY {
	IDLE,
	WALK
};

struct SDLEventInfo
{
	static constexpr size_t MAX_EVENTS = 10;
	uint8_t num_events;
	EventType events[MAX_EVENTS];
};

struct SDLTextureInfo
{
	SDL_Texture * texture;
	int width;
	int height;
	SDL_Rect m_src;
	SDL_Rect m_dst;
};

struct SDLTextureOptions
{
	int width = -1; // if negative, render texture's original size
	int height = -1; // if negative, render texture's original size
	SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;
	uint8_t blend_alpha = 255;
	uint8_t color_mod[3] = {255, 255, 255};
};

} // namespace cge

#endif // info_hpp
