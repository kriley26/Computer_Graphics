/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef sprite_hpp
#define sprite_hpp

#include <chrono>
#include <thread>
#include <iostream>
#include <map>
#include <unordered_map>

#include "src/info.hpp"
#include "src/preprocessor.h"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/texture.hpp"
#include "src/movement.hpp"
#include "src/box.hpp"
#include "src/sound.hpp"
#include "src/sprite_sheet.hpp"
#include "src/animation.hpp"

using namespace std;

namespace cge {
	class Sprite
	{
	public:
		enum SpriteType {
			Player,
			NPC,
			Nature
		};

		const char* convert_type_enum[3] = {
			STRINGIFY(Player),
			STRINGIFY(NPC),
			STRINGIFY(Nature)
		};

		Sprite();
		Sprite(float x1, float y1, SDLInfo si1, SDLTextureInfo sti1, SDLTextureOptions sto1);
		Sprite(float x1, float y1, SDLInfo si1, std::string image_path, int width1, int height1);
		Sprite(float x1, float y1, SDLInfo si1, cge::Texture t1, int width1, int height1, float scrW, float scrH, Sound* s);
		Sprite(float x1, float y1, SDLInfo si1, cge::SpriteSheet* ss, int width1, int height1, float scrW, float scrH, Sound* s, SpriteType spriteType);
        Sprite(string arr[]);
		~Sprite();

		void print();
		void sleep(int milliseconds);
		void updateVector();
		void passVector(Vector v1);
        Box* getOutline();
		void reverseDirection(Vector::Direction, float position);
        void detectCollision(Sprite* s);
		void update_sprite();
		void draw_sprite(SDL_Rect cameraRect);
		void set_animation(DIRECTION_FACING d);
		int update_animation(int frame);
		string convert_type();

        string get_name();
        float get_x_pos();
		float get_center_x();
        float get_y_pos();
		float get_center_y();
		float get_width();
		float get_height();
        int get_angle();
        bool get_spinning();
        float get_screenwidth();
        float get_screenheight();
		SpriteType get_type();

		void set_x_pos(float pos);
		void set_y_pos(float pos);

		void set_Name(string name);
        void set_SDLInfo(SDLInfo si1);
        void set_Texture(cge::Texture t);
		void set_SpriteSheet(SpriteSheet* s);
        void set_screenHeight(float screenH);
        void set_screenWidth(float screenW);
        void set_Sound(Sound* s);
		void set_CurrentAnimation(Animation *a);
		void set_CurrentAction(ACTIVITY a);
		void set_type(SpriteType s);


	private:
		float x, y, width, height;
		string path;
		string name;
		bool face_backwards = false;
		bool is_spinning = false;
		int angle = 0;
		float screenWidth = 0;
		float screenHeight = 0;
		SpriteType type;
		unordered_map<int, Animation*> animations;

		SDLInfo si;
		SDLTextureInfo sti;
		SDLTextureOptions sto;
		Vector v;
		Texture texture;
		SpriteSheet* sheet;
		Box box;
		Sound* sound;
		Animation* animation;
		ACTIVITY curr_action = ACTIVITY::IDLE;
		
	};
}

#endif
