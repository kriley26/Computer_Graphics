/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef player_hpp
#define player_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/sprite.hpp"

namespace cge {
	class Player {
	private: 
        Sprite* sprite;
		std::string name;


	public:
		Player(std::string n, Sprite *s);
		~Player();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
        void stopMovement();
		Sprite* getCharacter();
	};
}

#endif
