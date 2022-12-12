/*
 Developed for JHU 605.668 Computer Gaming Engines
 
 Author: Keegan Riley
 */

#ifndef box_hpp
#define box_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"

namespace cge {

    class Box {
        
    private:
        float minX, minY, maxX, maxY, width, height;
        float prevMinX, prevMinY, prevMaxX, prevMaxY;
        
    public:
        Box();
        Box(float x1, float x2, float y1, float y2);
        ~Box();
        float getMinX();
        float getMaxX();
        float getMinY();
        float getMaxY();
        float getPrevMinX();
        float getPrevMinY();
        float getPrevMaxX();
        float getPrevMaxY();
        float getWidth();
        float getHeight();
        float moveXPos(float position);
        float moveYPos(float position);

        void updateValues(float x1, float y1);
    };
}

#endif
