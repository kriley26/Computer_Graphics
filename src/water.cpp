#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"
#include "src/water.hpp"

using namespace std;

namespace cge {

	Water::Water() {
		v = Vector(0, 0);
	}

	Water::Water(Sprite* water) {
		name = water->get_name();
		si = water->get_sdl_info();
		sto = water->get_sto();
		sti = water->get_sti();
		x = water->get_x_pos();
		y = water->get_y_pos();
		width = water->get_width();
		height = water->get_height();
		screenWidth = water->get_screenwidth();
		screenHeight = water->get_screenheight();
		type = Nature;
		box = Box(x, x + width, y, y + height);
		set_nature_type(water->get_nature_type());
		v = Vector(0, 0);
	}

	Water::Water(SDLInfo si1, SDLTextureOptions sto1, float x1, float y1, float width1, float height1) {
		si = si1;
		sto = sto1;
		sti.width = width1;
		sti.height = height1;
		sto.width = width1;
		sto.height = height1;
		x = x1;
		y = y1;
		width = width1;
		height = height1;
		type = Nature;
		box = Box(x, x + width, y, y + height);
		v = Vector(0, 0);
	}
	
	Water::Water(string arr[]) {
		name = arr[0];
		x = stof(arr[1]);
		y = stof(arr[2]);
		width = stof(arr[3]);
		height = stof(arr[4]);
		angle = stoi(arr[5]);
		istringstream(arr[6]) >> std::boolalpha >> is_spinning;
		screenWidth = stof(arr[7]);
		screenHeight = stof(arr[8]);
		if (strcmp("NA", arr[9].c_str()) == 0) {
			set_status(STATUS::NA);
		}
		else if (strcmp("UNCAPTURED", arr[9].c_str()) == 0) {
			set_status(STATUS::UNCAPTURED);
		}
		else if (strcmp("CAPTURED", arr[9].c_str()) == 0) {
			set_status(STATUS::CAPTURED);
		}
		if (strcmp("Player", arr[10].c_str()) == 0) {
			set_type(SpriteType::Player);
		}
		else if (strcmp("NPC", arr[10].c_str()) == 0) {
			set_type(SpriteType::NPC);
		}
		else if (strcmp("Nature", arr[10].c_str()) == 0) {
			set_type(SpriteType::Nature);
		}
		sti.width = width;
		sti.height = height;
		sto.width = width;
		sto.height = height;
		natureType = arr[11];
		v = Vector(0, 0);
	}

	void Water::draw_sprite(SDL_Rect rect) {
		sti.m_dst.x = x - rect.x;
		sti.m_dst.y = y - rect.y;
		sti.m_dst.w = sti.width;
		sti.m_dst.h = sti.height;

		SDL_SetRenderDrawColor(si.renderer, 0, 0, 100, 255);
		render_rect(si, sti, x, y, sto);
	}

	void Water::update_sprite() {}
}