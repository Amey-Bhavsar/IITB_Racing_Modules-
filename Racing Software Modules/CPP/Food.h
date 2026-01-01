#ifndef FOOD_H
#define Food_H

#include "Snake.h"

class Food {
	private:
		Point pos;
		int maxWidth, maxHeight;
	public:
		Food(int width, int height);

		void respawn();

		Point getPos() const { return pos; } 
};
#endif
