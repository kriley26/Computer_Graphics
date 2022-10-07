/*
Developed for JHU 605.558: Computer Gaming Engines

This is free and unencumbered software released into the public domain.
For more information, please refer to <https://unlicense.org>
*/

#include "src/image.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

namespace cge
{

void replace_all(std::string& in, const std::string& old_str, const std::string& new_str)
{
	size_t start_pos = 0;
	while ((start_pos = in.find(old_str, start_pos)) != std::string::npos) {
		in.replace(start_pos, old_str.length(), new_str);
		start_pos += new_str.length(); // Handles case where 'to' is a substring of 'from'
	}
}

void init_sdl_image()
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

SDLTextureInfo create_texture(const SDLInfo &sdl_info, const std::string &filepath)
{
	SDLTextureInfo result;

	std::string corrected_filepath(filepath);

#ifdef __BUILD_WIN__
	replace_all(corrected_filepath, "/", "\\");
#endif
	
	result.texture = IMG_LoadTexture(sdl_info.renderer, corrected_filepath.c_str());
	if( result.texture == nullptr ) 
	{
		std::cout << "Failed to load texture [" << corrected_filepath << "]: "
				  << IMG_GetError() << std::endl;
	} 
	else std::cout << "Loaded texture [" << corrected_filepath << "]" << std::endl;
	

	// https://wiki.libsdl.org/SDL_QueryTexture
	if( SDL_QueryTexture(result.texture, NULL, NULL, &result.width, &result.height) != 0 )
	{
		std::cout << "Failed to query texture [" << corrected_filepath << "]: " << SDL_GetError() << std::endl;
	}
	
	return result;
}

void destroy_texture(const SDLTextureInfo& texture_info)
{
	SDL_DestroyTexture(texture_info.texture);
}

void render_texture(const SDLInfo& sdl_info, const SDLTextureInfo &texture_info, int x_pos, int y_pos, std::optional<SDLTextureOptions> texture_mods)
{
	SDL_Rect rect;
	rect.x = x_pos;
	rect.y = y_pos;

	if( texture_mods != std::nullopt )
	{
		const auto& mods = texture_mods.value();
		rect.w = mods.width < 0 ? texture_info.width : mods.width;
		rect.h = mods.height < 0 ? texture_info.height : mods.height;

		if( mods.blend_mode != SDL_BLENDMODE_NONE )
		{
			if(SDL_SetTextureBlendMode(texture_info.texture, mods.blend_mode) != 0)
			{
				std::cout << "Failed to set Blend Mode: " << SDL_GetError() << std::endl;
			}

			if(SDL_SetTextureAlphaMod(texture_info.texture, mods.blend_alpha) != 0)
			{
				std::cout << "Failed to set Texture Alpha Mod: " << SDL_GetError() << std::endl;
			}
			
		}

		if(SDL_SetTextureColorMod(texture_info.texture, mods.color_mod[0], mods.color_mod[1], mods.color_mod[2]) != 0)
		{
			std::cout << "Failed to set Color Mod: " << SDL_GetError() << std::endl;
		}
	}
	else
	{
		rect.w = texture_info.width;
		rect.h = texture_info.height;
	}

	SDL_RenderCopy(sdl_info.renderer, texture_info.texture, NULL, &rect);
}

} // namespace cge



