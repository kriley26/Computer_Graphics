/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#include <chrono>
#include <iostream>
#include <thread>

#include "src/player.hpp"
#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/sprite.hpp"

namespace cge {

	Player::Player(std::string n, Sprite *s) {
		name = n;
		sprite = s;
	}

	Player::~Player() {}

	void Player::moveUp() {
		Vector v = Vector(0, -5);
		sprite->passVector(v);
	}

	void Player::moveDown() {
		Vector v = Vector(0, 5);
		sprite->passVector(v);
	}

	void Player::moveLeft() {
		Vector v = Vector(-5, 0);
		sprite->passVector(v);
	}

	void Player::moveRight() {
		Vector v = Vector(5, 0);
		sprite->passVector(v);
	}

    void Player::stopMovement() {
        Vector v = Vector(0, 0);
        sprite->passVector(v);
    }

	Sprite* Player::getCharacter() {
		return sprite;
	}
}
