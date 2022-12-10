#include <chrono>
#include <thread>
#include <iostream>
#include <map>
#include <unordered_map>

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

	unordered_map<int, Animation*> SpriteSheet::parse_animations() {
		unordered_map<int, Animation*> map = {};
		map.insert(pair<int, Animation*>(int(DIRECTION_FACING::LEFT), new Animation(0, 0, 300, 480, 2)));
		map.insert(pair<int, Animation*>(int(DIRECTION_FACING::UP), new Animation(600, 0, 300, 480, 3)));
		map.insert(pair<int, Animation*>(int(DIRECTION_FACING::RIGHT), new Animation(0, 480, 300, 480, 2)));
		map.insert(pair<int, Animation*>(int(DIRECTION_FACING::DOWN), new Animation(600, 480, 300, 480, 3)));
		return map;
	}

	SpriteSheet* import_spritesheet(string filepath) {
		SpriteSheet* p = NULL;
		SpriteSheet s(filepath);
		p = &s;
		return p;
	}
}
