#include <iostream>
#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"

using namespace std;

namespace cge {

	class Water : public Sprite {

	private:

	public:
		Water();
		Water(Sprite* water);
		Water(SDLInfo si1, SDLTextureOptions sto1, float x1, float y1, float width1, float height1);
		Water(string arr[]);
		void draw_sprite(SDL_Rect rect);
		void update_sprite();
	};
}