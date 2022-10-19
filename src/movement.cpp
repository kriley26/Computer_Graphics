/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#include <chrono>
#include <iostream>
#include <thread>

#include "src/movement.hpp"
#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/sprite.hpp"

namespace cge {

    Movement:: Movement() {
        t = NPC;
    }

    Movement::Movement(Type type) {
        t = type;
    }

    Movement::~Movement() {
        
    }

    void Movement::update() {
        if (t == NPC) {
            updateNPC();
        } else if (t == PLAYER) {
            updatePlayer();
        }
    }

    void Movement::updatePlayer() {
//        x = x + v.getX();
//        y = y + v.getY();
//
//        if (x + sto.width >= screenWidth || x <= 0) {
//            v.setX(-v.getX());
//            is_spinning = true;
//        }
//        if (y + sto.height >= screenHeight || y <= 0) {
//            v.setY(-v.getY());
//            is_spinning = true;
//        }
//
//        if (is_spinning) {
//            angle = angle + 10;
//        }
    }

    void Movement::updateNPC(){
        
    }

    
}
