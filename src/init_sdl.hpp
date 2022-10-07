/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#ifndef init_sdl_hpp
#define init_sdl_hpp

#include "src/info.hpp"

namespace cge
{

void init_sdl();
void create_sdl_components(SDLInfo &sdl_info, int window_width, int window_height);
void destroy_sdl_components(SDLInfo &sdl_info);

} // namespace cge

#endif // init_sdl_hpp
