/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef movement_hpp
#define movement_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/vector.hpp"
#include "src/sprite.hpp"

namespace cge {

    class Movement {
        
        enum Type {
            NPC,
            PLAYER
        };
        
    private:
        Type t;
        
    public:
        Movement();
        Movement(Type t);
        ~Movement();
        void update();
        void updateNPC();
        void updatePlayer();
    };
}

#endif
