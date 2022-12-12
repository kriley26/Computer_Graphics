#include <iostream>
#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"

using namespace std;

namespace cge {

	class CaptureZone : public Sprite {


	public:
		CaptureZone();
		CaptureZone(Sprite* cp);
		CaptureZone(SDLInfo si1, SDLTextureOptions sto1, float x1, float y1, float width1, float height1);
		CaptureZone(string arr[]);
		void draw_sprite(SDL_Rect rect);
		void update_sprite();
		void update_color();
		void update_status(STATUS s);
		STATUS get_status();

	private:
		uint8_t color_mod[3] = { 255, 255, 255 };
		STATUS status = UNCAPTURED;
	};
}