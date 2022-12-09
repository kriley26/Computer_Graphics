/*
Developed for JHU 605.668 Computer Gaming Engines

Author: Keegan Riley
*/

#ifndef vector_hpp
#define vector_hpp

#include <chrono>
#include <thread>

#include "src/info.hpp"
#include "src/image.hpp"

namespace cge {

	class Vector {

	private:
        float x = 0.0;
        float y = 0.0;

	public:
        enum Direction {
            LEFT_DIR,
			RIGHT_DIR,
            TOP_DIR,
			BOTTOM_DIR
        };
		Vector();
		Vector(float x1, float y1);
		~Vector();
		float getX();
		void setX(float x1);
		float getY();
		void setY(float y1);
		double getLength();
		void normalize();
		Vector addVector(Vector v);
		void scale(int var);
		float dotProd(Vector v);
        void reverseDirection(Direction d);
	};
}

#endif
