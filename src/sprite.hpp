/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef sprite_hpp
#define sprite_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/texture.hpp"
#include "src/movement.hpp"
#include "src/box.hpp"
#include "src/sound.hpp"

namespace cge {
	class Sprite
	{
	private:
		float x, y;
		int dir;
		std::string path;
		std::string name;
		bool face_backwards = false;
		bool is_spinning = false;
		int angle = 0;
        int screenWidth = 0;
        int screenHeight = 0;

		SDLInfo si;
		SDLTextureInfo sti;
		SDLTextureOptions sto;
		Vector v;
		Texture texture;
        Box box;
        Sound* sound;

	public:
        Sprite();
		Sprite(int x1, int y1, SDLInfo si1, SDLTextureInfo sti1, SDLTextureOptions sto1);
		Sprite(int x1, int y1, SDLInfo si1, std::string image_path, int width1, int height1);
		Sprite(int x1, int y1, SDLInfo si1, cge::Texture t1, int width1, int height1, int scrW, int scrH, Sound* s);
		~Sprite();
		void sleep(int milliseconds);
		void updateVector();
		void passVector(Vector v1);
        Box getOutline();
        void detectCollision(Sprite s);
		void update_sprite();
		void draw_sprite();
	};
}

#endif
