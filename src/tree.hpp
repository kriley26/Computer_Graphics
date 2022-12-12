#include <iostream>
#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"

using namespace std;

namespace cge {

	class Tree : public Sprite {

	private:

	public:
		Tree();
		Tree(Sprite* tree);
		Tree(SDLInfo si1, SDLTextureOptions sto1, float x1, float y1, float width1, float height1);
		Tree(string arr[]);
		void draw_sprite(SDL_Rect rect);
		void update_sprite();
	};
}