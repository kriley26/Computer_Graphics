#include "src/animation.hpp"

namespace cge {

	Animation::Animation() {

	}

	Animation::Animation(int x1, int y1, int width, int height, int f) {
		x = x1;
		y = y1;
		w = width;
		h = height;
		maxFrames = f;
	}

	void Animation::reset() {

	}
	
}