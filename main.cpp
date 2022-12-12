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
#include <SDL2/SDL_ttf.h>

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
using namespace cge;

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

int show_main_menu(cge::SDLInfo info, TTF_Font* font) {

	SDL_Surface* screen = SDL_GetWindowSurface(info.window);
	Uint32 time;
	int x, y;
	const int NUMMENU = 3;
	const char* labels[NUMMENU] = { "New Game", "Load Game", "Exit" };
	SDL_Surface* options[NUMMENU];
	bool selected[NUMMENU] = { 0, 0, 0 };
	SDL_Color color[2] = { {255, 255, 255}, {255, 0, 0} };
	
	options[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	options[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	options[2] = TTF_RenderText_Solid(font, labels[2], color[0]);
	
	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w / 2 - options[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - options[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - options[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2;
	pos[2].x = screen->clip_rect.w / 2 - options[0]->clip_rect.w / 2;
	pos[2].y = screen->clip_rect.h / 2 + options[0]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(info.window);

	SDL_Event event;
	while (1) {
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU; i++)
					SDL_FreeSurface(options[i]);
				return 2;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i++) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						if (!selected[i]) {
							selected[i] = 1;
							SDL_FreeSurface(options[i]);
							options[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
					else {
						if (selected[i]) {
							selected[i] = 0;
							SDL_FreeSurface(options[i]);
							options[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i++) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						for (int j = 0; j < NUMMENU; j++)
							SDL_FreeSurface(options[j]);
						return i;
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					for (int i = 0; i < NUMMENU; i++) {
						SDL_FreeSurface(options[i]);
					}
					return 2;
				}
			}
		}
		for (int i = 0; i < NUMMENU; i++)
			SDL_BlitSurface(options[i], NULL, screen, &pos[i]);
		SDL_UpdateWindowSurface(info.window);
		if (1000 / 30 > (SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}
	
}

int show_pause_menu(cge::SDLInfo info, TTF_Font* font) {

	SDL_Surface* screen = SDL_GetWindowSurface(info.window);
	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = { "Continue", "Exit" };
	SDL_Surface* options[NUMMENU];
	bool selected[NUMMENU] = { 0, 0 };
	SDL_Color color[2] = { {255, 255, 255}, {255, 0, 0} };

	options[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	options[1] = TTF_RenderText_Solid(font, labels[1], color[0]);

	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w / 2 - options[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - options[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - options[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 + options[0]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(info.window);

	SDL_Event event;
	while (1) {
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU; i++)
					SDL_FreeSurface(options[i]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i++) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						if (!selected[i]) {
							selected[i] = 1;
							SDL_FreeSurface(options[i]);
							options[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
					else {
						if (selected[i]) {
							selected[i] = 0;
							SDL_FreeSurface(options[i]);
							options[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i++) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						for (int j = 0; j < NUMMENU; j++)
							SDL_FreeSurface(options[j]);
						return i;
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					for (int i = 0; i < NUMMENU; i++) {
						SDL_FreeSurface(options[i]);
					}
					return 1;
				}
			}
		}
		for (int i = 0; i < NUMMENU; i++)
			SDL_BlitSurface(options[i], NULL, screen, &pos[i]);
		SDL_UpdateWindowSurface(info.window);
		if (1000 / 30 > (SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}

}

int main(int argc, char *argv[])
{    
	cge::init_sdl();
	TTF_Init();

	cge::SDLInfo sdl_info;

	constexpr int SCREEN_WIDTH = 650;
	constexpr int SCREEN_HEIGHT = 650;
	SDL_Rect cameraRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	int levelWidth, levelHeight;

	cge::create_sdl_components(sdl_info, SCREEN_WIDTH, SCREEN_HEIGHT);
	cge::init_sdl_image();
    cge::init_sdl_mixer();
	//SDL_SetRenderDrawColor(sdl_info.renderer, 0, 0, 0, 255);

	auto resource_path = std::string(TOSTRING(RESOURCE_DIR));

    // Image File Paths
	auto brad_texture_path = resource_path + string("images/thebrad.png");
	auto chad_texture_path = resource_path + string("images/thechad.png");
	auto man_texture_path = resource_path + string("images/theman.png");
	auto background_path = resource_path + string("backgrounds/main_background.PNG");
    
    // Audio File Paths
    auto background_one_path = resource_path + std::string("audio/game_select.mp3");
    auto backgroung_two_path = resource_path + std::string("audio/sunny_side_up.mp3");
    auto wall_hit_path = resource_path + std::string("audio/mk64_boo_laugh.wav");
    auto character_hit_path = resource_path + std::string("audio/mk64_bowser02.wav");

	// Sprite Sheets
	cge::SpriteSheet* chad_sheet = new cge::SpriteSheet(chad_texture_path);
	cge::SpriteSheet* brad_sheet = new cge::SpriteSheet(brad_texture_path);
	cge::SpriteSheet* man_sheet = new cge::SpriteSheet(man_texture_path);
    
    cge::Sound sound;
    sound.loadFiles(0, &background_one_path);
    sound.loadFiles(1, &backgroung_two_path);
    sound.loadFiles(2, &wall_hit_path);
    sound.loadFiles(3, &character_hit_path);

	cge::SDLTextureInfo background = cge::create_texture(sdl_info, background_path);
	SDL_QueryTexture(background.texture, NULL, NULL, &levelWidth, &levelHeight);

	TTF_Font* font;
	auto file = resource_path + std::string("fonts/Pacifico.ttf");
	font = TTF_OpenFont(file.c_str(), 20);

	bool run_game = true;
	double updateSpeed = .075;
	double drawSpeed = .016667;
	double changeVectorSpeed = 5;
	int updateCount = 0;
	int drawCount = 0;
    std::string jsonFile = "";
    cge::Sprite* playerSprite = NULL;

	std::vector<cge::Sprite*> npcSprites;
	std::vector<cge::Sprite*> allSprites;
    
    sound.playFile(sound.getBackground(0).c_str());
    int frameNum = 0;

	int menuSelection = show_main_menu(sdl_info, font);
	if (menuSelection == 0) {
		playerSprite = new cge::Sprite(1, 1, sdl_info, man_sheet, 75, 125, background.width, background.height, &sound, cge::Sprite::Player);
	} 
	else if (menuSelection == 1) {
		if (FILE* file = fopen((resource_path + "save_data/save.json").c_str(), "r")) {
			std::cout << "File present" << endl;
			std::string text;
			ifstream myFile(resource_path + "save_data/save.json");

			while (getline(myFile, text)) {
				if (playerSprite == NULL) {
					playerSprite = cge::parse_data(text);
					playerSprite->set_SDLInfo(sdl_info);
					playerSprite->set_SpriteSheet(man_sheet);
					playerSprite->set_screenWidth(background.width);
					playerSprite->set_screenHeight(background.height);
					playerSprite->set_Sound(&sound);
				}

			}

		}
	}
	else if (menuSelection == 2) {
		run_game = false;
	}

	cge::Player player(std::string(TOSTRING("Player 1")), playerSprite);
	allSprites.push_back(playerSprite);
	std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nStart time: " << start_time << "\n";
    
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
				case cge::EventType::PAUSE:
					menuSelection = show_pause_menu(sdl_info, font);
					if (menuSelection == 1)
						run_game = false;
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

		cameraRect.x = player.getCharacter()->get_x_pos() - (float(SCREEN_WIDTH / 2));
		cameraRect.y = player.getCharacter()->get_y_pos() - (float(SCREEN_HEIGHT / 2));

		if (cameraRect.x < 0)
			cameraRect.x = 0;
		if (cameraRect.y < 0)
			cameraRect.y = 0;
		
		if (cameraRect.x + cameraRect.w >= levelWidth)
			cameraRect.x = levelWidth - SCREEN_WIDTH;
		if (cameraRect.y + cameraRect.h >= levelHeight)
			cameraRect.y = levelHeight - SCREEN_HEIGHT;

		if (get_time(since_draw, drawSpeed)) {
			SDL_RenderClear(sdl_info.renderer);
			SDL_RenderCopy(sdl_info.renderer, background.texture, &cameraRect, NULL);
			for (cge::Sprite* s : allSprites) {
				s->draw_sprite(cameraRect);
			}
			drawCount++;
			since_draw = std::chrono::system_clock::now();
			SDL_RenderPresent(sdl_info.renderer);
		}

		if (get_time(since_change_vec, changeVectorSpeed)) {
			for (cge::Sprite* sprite : npcSprites) {
				if (sprite->get_type() == cge::Sprite::SpriteType::NPC) {
					sprite->updateVector();
				}
			}
			since_change_vec = std::chrono::system_clock::now();
		}
	}

    cge::save_game(allSprites);
	std::cout << "\nUpdate Count: " << updateCount << "\nDrawCount: " << drawCount;
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "\nEnd time: " << end_time << "\n";

	//cge::destroy_texture(box_texture);
	cge::destroy_texture(background);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
