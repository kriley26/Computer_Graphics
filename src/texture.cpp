#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "src/texture.hpp"
#include "src/info.hpp"
#include "src/image.hpp"

using namespace std;

namespace cge {

	Texture::Texture() {

	}

	Texture::~Texture() {

	}

	void Texture::add_jump(string str) {
		jump_texture = str;
	}

	void Texture::add_walk(vector<string*> v1) {
		walk_textures = v1;
	}

	std::string Texture::get_motion(int val) {
		switch (val) {
		case 1:
			return *walk_textures[0];
		case 2:
			return *walk_textures[1];
		case 3:
			return jump_texture;
		default:
			break;
		}
        return 0;
	}
}
