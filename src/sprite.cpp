#include <chrono>
#include <iostream>
#include <thread>

#include "src/sprite.hpp"
#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/movement.hpp"


namespace cge {

	Sprite::Sprite(int x1, int y1, SDLInfo si1, SDLTextureInfo sti1, SDLTextureOptions sto1) {
		si = si1;
		sti = sti1;
		sto = sto1;
		x = x1;
		y = y1;
		dir = 1;
	}

	Sprite::Sprite(int x1, int y1, SDLInfo si1, std::string image_path, int width1, int height1) {
		si = si1;
		sti = create_texture(si, image_path);
		sto.width = width1;
		sto.height = height1;
		path = image_path;
		x = x1;
		y = y1;
		dir = 1;
		name = "Mario";
	}

	Sprite::Sprite(int x1, int y1, SDLInfo si1, Texture t1, int width1, int height1, int scrW, int scrH, Sound* s) {
		si = si1;
        texture = t1;
		sti = create_texture(si, texture.get_motion(1));
		sto.width = width1;
		sto.height = height1;
		path = t1.get_motion(1);
		x = x1;
		y = y1;
        box = Box(x, x+width1, y, y+height1);
		dir = 1;
        screenWidth = scrW;
        screenHeight = scrH;
		name = "Mario";
        v = Vector(0, 0);
        sound = s;
	}

	Sprite::~Sprite() {
		destroy_texture(sti);
	}

	void Sprite::sleep(int milliseconds) {

		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	void Sprite::updateVector() {
		v = Vector();
		is_spinning = false;
		angle = 0;
		if (v.getX() < 0) {
			face_backwards = true;
		}
		else {
			face_backwards = false;
		}
	}

	void Sprite::passVector(Vector v1) {
		v = v1;
		is_spinning = false;
		if (v.getX() < 0) {
			face_backwards = true;
		}
		else {
			face_backwards = false;
		}
	}

    void Sprite::detectCollision(Sprite s) {
        //Check if sprite is overlapping in x direction & reverse direction
        
        // Left Hand Check
        if (box.getMaxX() >= s.box.getMinX() && box.getMaxX() < s.box.getMaxX()) {
            v.reverseDirection(Vector::X_DIR);
            sound->playFile(sound->getHit(0).c_str());
        } // Right Hand Check
        else if (box.getMinX() <= s.box.getMaxX() && box.getMinX() > s.box.getMinX()) {
            v.reverseDirection(Vector::X_DIR);
            sound->playFile(sound->getHit(0).c_str());
        } // Top Check
        else if (box.getMaxY() <= s.box.getMinY() && box.getMaxY() < s.box.getMaxY()) {
            v.reverseDirection(Vector::Y_DIR);
            sound->playFile(sound->getHit(0).c_str());
        }
        else if (box.getMinY() >= s.box.getMaxY() && box.getMinY() > s.box.getMinY()) {
            v.reverseDirection(Vector::Y_DIR);
            sound->playFile(sound->getHit(0).c_str());
        }
    }

	void Sprite::update_sprite() {
		x = x + v.getX();
		y = y + v.getY();
        
        box.updateValues(v.getX(), v.getY());

		if (x + sto.width >= screenWidth || x <= 0) {
			v.setX(-v.getX());
			is_spinning = true;
            sound->playFile(sound->getHit(1).c_str());
		}
		if (y + sto.height >= screenHeight || y <= 0) {
			v.setY(-v.getY());
			is_spinning = true;
            sound->playFile(sound->getHit(1).c_str());
		}

		if (is_spinning) {
			angle = angle + 10;
		}
        
	}

	void Sprite::draw_sprite() {        
        Texture* t = &texture;
        if (t != nullptr && v.getX() != 0) {
            sti = update_texture(si, sti, texture.get_motion(2));
        } else if (t != nullptr && v.getY() < 0) {
            sti = update_texture(si, sti, texture.get_motion(3));
        } else {
            sti = update_texture(si, sti, texture.get_motion(1));
        }
        
		if (face_backwards) {
			render_texture(si, sti, x, y, angle, SDL_FLIP_HORIZONTAL, sto);
		}
		else {
			render_texture(si, sti, x, y, angle, SDL_FLIP_NONE, sto);
		}
	}
}
