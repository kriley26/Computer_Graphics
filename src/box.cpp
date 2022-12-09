#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"
#include "src/box.hpp"

namespace cge {

    Box::Box() {
        minX = 0;
        maxX = 0;
        minY = 0;
        maxY = 0;
        width = 0;
        height = 0;
    }

    Box::Box(float x1, float x2, float y1, float y2) {
        minX = x1;
        maxX = x2;
        minY = y1;
        maxY = y2;
        width = maxX - minX;
        height = maxY - minY;
    }

    Box::~Box() {
        
    }

    float Box::getMinX() {
        return minX;
    }

    float Box::getMaxX() {
        return maxX;
    }

    float Box::getMinY() {
        return minY;
    }

    float Box::getMaxY() {
        return maxY;
    }

    float Box::getWidth() {
        return width;
    }

    float Box::getHeight() {
        return height;
    }

    float Box::moveXPos(float position) {
        maxX = position;
        minX = position - width;
        return minX;
    }

    float Box::moveYPos(float position) {
        maxY = position;
        minY = position - height;
        return minY;
    }

    void Box::updateValues(float x1, float y1) {
        minX = minX + x1;
        maxX = maxX + x1;
        minY = minY + y1;
        maxY = maxY + y1;
    }
}
