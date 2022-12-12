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
#include "src/tree.hpp"
#include "src/water.hpp"
#include "src/capture_zone.hpp"

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

int game_over_screen(cge::SDLInfo info, TTF_Font* font) {

	SDL_Surface* screen = SDL_GetWindowSurface(info.window);
	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = { "You Win", "Game Over" };
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

	// Level Paths 
	auto level_one_path = resource_path + std::string("levels/level1.txt");
    
    cge::Sound sound;
    sound.loadMusic(background_one_path.c_str());
    sound.loadMusic(backgroung_two_path.c_str());
    sound.loadSound(wall_hit_path.c_str());
    sound.loadSound(character_hit_path.c_str());

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

	cge::SDLTextureOptions treeOpts;
	treeOpts.color_mod[0] = 0;
	treeOpts.color_mod[1] = 255;
	treeOpts.color_mod[2] = 0;

	Tree* t1 = NULL;
	Tree* t2 = NULL;
	Tree* t3 = NULL;
	Tree* t4 = NULL;
	Tree* t5 = NULL;
	Tree* t6 = NULL;
	Tree* t7 = NULL;
	Tree* t8 = NULL;
	Tree* t9 = NULL;
	Tree* t0 = NULL;

	Water* w1 = NULL;
	Water* w2 = NULL;
	Water* w3 = NULL;
	Water* w4 = NULL;
	Water* w5 = NULL;
	Water* w6 = NULL;
	Water* w7 = NULL;
	Water* w8 = NULL;
	Water* w9 = NULL;
	Water* w0 = NULL;

	CaptureZone* cz1 = NULL;
	CaptureZone* cz2 = NULL;
	CaptureZone* cz3 = NULL;
	CaptureZone* cz4 = NULL;
	CaptureZone* cz5 = NULL;

	Tree* tree[10] = { t1, t2, t3, t4, t5, t6, t7, t8, t9, t0 };
	Water* water[10] = { w1, w2, w3, w4, w5, w6, w7, w8, w9, w0 };
	CaptureZone* czone[5] = { cz1, cz2, cz3, cz4, cz5 };

	std::vector<cge::Sprite*> npcSprites;
	std::vector<cge::Sprite*> allSprites;
	uint8_t spriteCount[3] = { 0, 0, 0 };
    
	sound.getBackground(0);
    int frameNum = 0;

	int menuSelection = show_main_menu(sdl_info, font);
	if (menuSelection == 0) {
		playerSprite = new cge::Sprite(1, 1, sdl_info, man_sheet, 50, 90, background.width, background.height, &sound, cge::Sprite::Player);
		if (FILE* file = fopen(level_one_path.c_str(), "r")) {
			string text;
			ifstream level(level_one_path);
			Sprite* s;
			int ti = 0;
			int wi = 0;
			int czi = 0;
			while (getline(level, text)) {
				s = cge::parse_level(text);
				s->set_SDLInfo(sdl_info);
				s->set_screenWidth(background.width);
				s->set_screenHeight(background.height);

				if (strcmp("Tree", s->get_nature_type().c_str()) == 0) {
					if (tree[ti] == NULL) {
						tree[ti] = new Tree(s);
					}
					ti++;
				} else if (strcmp("Water", s->get_nature_type().c_str()) == 0) {
					if (water[wi] == NULL) {
						water[wi] = new Water(s);
					}
					wi++;
				}
				else if (strcmp("CaptureZone", s->get_nature_type().c_str()) == 0) {
					if (czone[czi] == NULL) {
						czone[czi] = new CaptureZone(s);
					}
					czi++;
				}
			}
			for (int i = 0; i < 10; i++) {
				if (tree[i] != NULL) {
					allSprites.push_back(tree[i]);
				}
			}
			for (int i = 0; i < 10; i++) {
				if (water[i] != NULL) {
					allSprites.push_back(water[i]);
				}
			}
			for (int i = 0; i < 5; i++) {
				if (czone[i] != NULL) {
					allSprites.push_back(czone[i]);
				}
			}

		}
	} 
	else if (menuSelection == 1) {
		if (FILE* file = fopen((resource_path + "save_data/save.json").c_str(), "r")) {
			std::cout << "File present" << endl;
			std::string text;
			ifstream myFile(resource_path + "save_data/save.json");
			Sprite* s;
			int ti = 0;
			int wi = 0;
			int czi = 0;

			while (getline(myFile, text)) {
				s = cge::parse_data(text);
				if (strcmp("", s->get_nature_type().c_str()) == 0 && playerSprite == NULL) {
					playerSprite = cge::parse_data(text);
					playerSprite->set_SDLInfo(sdl_info);
					playerSprite->set_SpriteSheet(man_sheet);
					playerSprite->set_screenWidth(background.width);
					playerSprite->set_screenHeight(background.height);
					playerSprite->set_Sound(&sound);
				}
				else {
					s->set_SDLInfo(sdl_info);
					s->set_screenWidth(background.width);
					s->set_screenHeight(background.height);

					if (strcmp("Tree", s->get_nature_type().c_str()) == 0) {
						if (tree[ti] == NULL) {
							tree[ti] = new Tree(s);
						}
						ti++;
					}
					else if (strcmp("Water", s->get_nature_type().c_str()) == 0) {
						if (water[wi] == NULL) {
							water[wi] = new Water(s);
						}
						wi++;
					}
					else if (strcmp("CaptureZone", s->get_nature_type().c_str()) == 0) {
						if (czone[czi] == NULL) {
							czone[czi] = new CaptureZone(s);
						}
						czi++;
					}
				}

			}
			for (int i = 0; i < 10; i++) {
				if (tree[i] != NULL) {
					allSprites.push_back(tree[i]);
				}
			}
			for (int i = 0; i < 10; i++) {
				if (water[i] != NULL) {
					allSprites.push_back(water[i]);
				}
			}
			for (int i = 0; i < 5; i++) {
				if (czone[i] != NULL) {
					allSprites.push_back(czone[i]);
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
	std::time_t start_pause_time = 0;
	std::time_t stop_pause_time = 0;
	std::time_t total_pause_time = 0;

	int total = 0;
	int captured = 0;
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
				case cge::EventType::INTERACT:
					for (cge::Sprite* s : allSprites) {
						if (strcmp(s->get_nature_type().c_str(), "CaptureZone") == 0) {
							player.getCharacter()->capture_zone(s);
						}
					}
					total = 0;
					captured = 0;
					for (cge::Sprite* s : allSprites) {
						if (strcmp(s->get_nature_type().c_str(), "CaptureZone") == 0) {
							total++;
							if (s->get_status() == Sprite::CAPTURED) {
								captured++;
							}
						}
					}
					if (total > 0 && total == captured) {
						game_over_screen(sdl_info, font);
						run_game = false;
					}
					break;
				case cge::EventType::PAUSE:
					start_pause_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					menuSelection = show_pause_menu(sdl_info, font);
					stop_pause_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					total_pause_time = total_pause_time + (stop_pause_time - start_pause_time);
					if (menuSelection == 1)
						run_game = false;
					break;
				default:
					break;
			}
		}

		if (get_time(since_update, updateSpeed)) {
			for (cge::Sprite* s : allSprites) {
				player.getCharacter()->detectCollision(s);
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
			for (Sprite* s : allSprites) {
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
	std::cout << "\nTime running: " << end_time - start_time << " seconds" << endl;
	std::cout << "\nTime paused: " << stop_pause_time - start_pause_time << " seconds" << endl;

	//cge::destroy_texture(box_texture);
	cge::destroy_texture(background);
	cge::destroy_sdl_components(sdl_info);
	return 0;
}
