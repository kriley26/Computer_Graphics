#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include "src/vector.hpp"
#include "src/info.hpp"
#include "src/image.hpp"

namespace cge {

	Vector::Vector() {
		srand((unsigned)time(NULL));
		float xRand = float(rand() % 10 - 5);
		float yRand = float(rand() % 10 - 5);
		x = xRand;
		y = yRand;
	}

	Vector::Vector(float x1, float y1) {
		x = x1;
		y = y1;
	}

	Vector::~Vector(){}

	float Vector::getX() {
		return x;
	}

	void Vector::setX(float x1) {
		x = x1;
	}

	float Vector::getY() {
		return y;
	}

	void Vector::setY(float y1) {
		y = y1;
	}

	double Vector::getLength() {
		double xSqr = pow(x, 2);
		double ySqr = pow(y, 2);
		double mag = sqrt(xSqr + ySqr);
		return mag;
	}

	void Vector::normalize() {
		double mag = getLength();

		x = (x / mag);
		y = (y / mag);
	}

	Vector Vector::addVector(Vector v) {
		float tempX = x + v.getX();
		float tempY = y + v.getY();

		return Vector(tempX, tempY);
	}

	void Vector::scale(int var) {
		x = var * x;
		y = var * y;
	}

	float Vector::dotProd(Vector v) {
		float xSum = x * v.getX();
		float ySum = y * v.getY();

		return xSum + ySum;
	}

    void Vector::reverseDirection(Direction d) {
        switch (d) {
            case LEFT_DIR:
				if (x > 0) {
					x = -x;
				}
				else if (x == 0) {
					x = -1;
				}
                break;
            case RIGHT_DIR:
				if (x < 0) {
					x = -x;
				}
				else if (x == 0) {
					x = 1;
				}
                break;
			case TOP_DIR:
				if (y > 0) {
					y = -y;
				}
				else if (y == 0) {
					y = -1;
				}
				break;
			case BOTTOM_DIR:
				if (y < 0) {
					y = -y;
				}
				else if (y == 0) {
					y = 1;
				}
				break;
            default:
                break;
        }
    }
}
