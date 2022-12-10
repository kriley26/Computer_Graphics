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
		sprite->set_Name(name);
	}

	Player::~Player() {}

	void Player::moveUp() {
		Vector v = Vector(0, -5);
		sprite->passVector(v);
		sprite->set_CurrentAction(ACTIVITY::WALK);
        sprite->set_animation(DIRECTION_FACING::UP);
	}

	void Player::moveDown() {
		Vector v = Vector(0, 5);
		sprite->passVector(v);
		sprite->set_CurrentAction(ACTIVITY::WALK);
        sprite->set_animation(DIRECTION_FACING::DOWN);
	}

	void Player::moveLeft() {
		Vector v = Vector(-5, 0);
		sprite->passVector(v);
		sprite->set_CurrentAction(ACTIVITY::WALK);
        sprite->set_animation(DIRECTION_FACING::RIGHT);
	}

	void Player::moveRight() {
		Vector v = Vector(5, 0);
		sprite->passVector(v);
		sprite->set_CurrentAction(ACTIVITY::WALK);
        sprite->set_animation(DIRECTION_FACING::RIGHT);
	}

    void Player::stopMovement() {
        Vector v = Vector(0, 0);
        sprite->passVector(v);
		sprite->set_CurrentAction(ACTIVITY::IDLE);
    }

	Sprite* Player::getCharacter() {
		return sprite;
	}
}
