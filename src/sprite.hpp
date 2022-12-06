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

using namespace std;

namespace cge {
	class Sprite
	{
	private:
		float x, y;
		int dir;
		string path;
		string name;
		bool face_backwards = false;
		bool is_spinning = false;
		int angle = 0;
        float screenWidth = 0;
        float screenHeight = 0;

		SDLInfo si;
		SDLTextureInfo sti;
		SDLTextureOptions sto;
		Vector v;
		Texture texture;
        Box box;
        Sound* sound;

	public:
        Sprite();
		Sprite(float x1, float y1, SDLInfo si1, SDLTextureInfo sti1, SDLTextureOptions sto1);
		Sprite(float x1, float y1, SDLInfo si1, std::string image_path, int width1, int height1);
		Sprite(float x1, float y1, SDLInfo si1, cge::Texture t1, int width1, int height1, float scrW, float scrH, Sound* s);
        Sprite(string arr[]);
		~Sprite();
		void sleep(int milliseconds);
		void updateVector();
		void passVector(Vector v1);
        Box* getOutline();
        void detectCollision(Sprite* s);
		void update_sprite();
		void draw_sprite();

        string get_name();
        float get_x_pos();
        float get_y_pos();
        int get_angle();
        bool get_spinning();
        float get_screenwidth();
        float get_screenheight();

        void set_SDLInfo(SDLInfo si1);
        void set_Texture(cge::Texture t);
        void set_screenHeight(float screenH);
        void set_screenWidth(float screenW);
        void set_Sound(Sound* s);
	};
}

#endif
