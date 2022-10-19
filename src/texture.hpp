/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef texture_hpp
#define texture_hpp

#include <chrono>
#include <thread>
#include <vector>

#include "src/info.hpp"
#include "src/image.hpp"

using namespace std;

namespace cge {
	class Texture {
	private:
		vector<string*> walk_textures;
		string jump_texture;
	public:
		Texture();
		~Texture();
		void add_jump(string v1);
		void add_walk(vector<string*> v1);
		string get_motion(int val);
	};
}


#endif 