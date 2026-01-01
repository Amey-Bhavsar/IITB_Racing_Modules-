#include "Snake.h"

Snake::Snake(int startX, int startY){
	body.push_back({startX, startY});
	body.push_back({startX - 1, startY});
	body.push_back({startX - 2, startY});

	dir = RIGHT;
}

void Snake::changeDirection(Direction newDir) {
	if ((dir == UP && newDir != DOWN) ||
        (dir == DOWN && newDir != UP) ||
        (dir == LEFT && newDir != RIGHT) ||
        (dir == RIGHT && newDir != LEFT)) {
        dir = newDir;
    }
}

void Snake::move() {
	Point newHead = body[0];
	if (dir == UP) newHead.y--;
	else if (dir == DOWN) newHead.y++;
	else if (dir == LEFT) newHead.x--;
	else if (dir == RIGHT) newHead.x++;

	body.insert(body.begin(), newHead);
	body.pop_back();
}

void Snake::grow(){
	body.push_back(body.back());
}
