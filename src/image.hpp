/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#ifndef image_hpp
#define image_hpp

#include <optional>
#include <string>

#include "src/info.hpp"

namespace cge
{

void init_sdl_image();

SDLTextureInfo create_texture(const SDLInfo& sdl_info, const std::string &filepath);
SDLTextureInfo update_texture(const SDLInfo& sdl_info, const SDLTextureInfo& sdl_texture, const std::string &filepath);
void destroy_texture(const SDLTextureInfo& texture_info);

void render_texture(const SDLInfo& sdl_info, const SDLTextureInfo &texture_info, int x_pos, int y_pos, std::optional<SDLTextureOptions> texture_mods = std::nullopt);
void render_texture(const SDLInfo& sdl_info, const SDLTextureInfo &texture_info, int x_pos, int y_pos, double angle, SDL_RendererFlip flip, std::optional<SDLTextureOptions> texture_mods = std::nullopt);

} // namespace cge

#endif // image_hpp
