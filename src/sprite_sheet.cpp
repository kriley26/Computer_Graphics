#include <chrono>
#include <thread>
#include <map>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/sprite.hpp"
#include "src/sprite_sheet.hpp"
#include "src/animation.hpp"

using namespace std;

namespace cge {

	SpriteSheet::SpriteSheet() {

	}

	SpriteSheet::SpriteSheet(string filepath1) {
		filepath = filepath1;
	}

	SpriteSheet::~SpriteSheet() {

	}

	string SpriteSheet::get_file() {
		return filepath;
	}

	map<DIRECTION_FACING, Animation> SpriteSheet::parse_animations() {
		map<DIRECTION_FACING, Animation> map;
		map.emplace(DIRECTION_FACING::LEFT, new Animation(0, 0, 300, 480, 2));
		map.emplace(DIRECTION_FACING::UP, new Animation(600, 0, 300, 480, 3));
		map.emplace(DIRECTION_FACING::RIGHT, new Animation(0, 480, 300, 480, 2));
		map.emplace(DIRECTION_FACING::DOWN, new Animation(600, 480, 300, 480, 3));
		return map;
	}

	SpriteSheet* import_spritesheet(string filepath) {
		SpriteSheet* p = NULL;
		SpriteSheet s(filepath);
		p = &s;
		return p;
	}
}
