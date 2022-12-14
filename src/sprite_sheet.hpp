/*
 Developed for JHU 605.668 Computer Gaming Engines

 Author: Keegan Riley
 */

#ifndef sprite_sheet_hpp
#define sprite_sheet_hpp

#include <chrono>
#include <thread>
#include <map>
#include <unordered_map>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"
#include "src/animation.hpp"

using namespace std;

namespace cge {

	class SpriteSheet {
	private:
		string filepath;
	public:
		SpriteSheet();
		SpriteSheet(string filepath);
		~SpriteSheet();
		string get_file();
		unordered_map<int, Animation*> parse_animations();
	};

	SpriteSheet* import_spritesheet(string filepath);
	
}

#endif
