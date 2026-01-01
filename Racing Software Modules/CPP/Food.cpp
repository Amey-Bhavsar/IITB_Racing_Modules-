#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food(int width, int height) {
	maxWidth = width;
	maxHeight = height;

	srand(time(0));
	respawn();
}

void Food::respawn(){
	pos.x = (rand() % (maxWidth - 2)) + 1;
    pos.y = (rand() % (maxHeight - 2)) + 1;
}
