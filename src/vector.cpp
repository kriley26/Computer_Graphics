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
		int xRand = rand() % 10 - 5;
		int yRand = rand() % 10 - 5;
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

	float Vector::getLength() {
		float xSqr = pow(x, 2);
		float ySqr = pow(y, 2);
		float mag = sqrt(xSqr + ySqr);
		return mag;
	}

	void Vector::normalize() {
		float mag = getLength();

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
}
