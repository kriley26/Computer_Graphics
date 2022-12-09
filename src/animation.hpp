/*
 Developed for JHU 605.668 Computer Gaming Engines

 Author: Keegan Riley
 */

#ifndef animation_hpp
#define animation_hpp

namespace cge {

	class Animation {

	private:

	public:
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int maxFrames = 0;

		Animation();
		Animation(int x1, int y1, int width, int height, int f);
		void reset();

	};
};


#endif
