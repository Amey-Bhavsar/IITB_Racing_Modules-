#ifndef SNAKE_H
#define SNAKE_H

#include<vector>
#include<ncurses.h>

struct Point {
	int x, y;
};

enum Direction { UP , DOWN , LEFT , RIGHT };

class Snake {
	private:
		std::vector<Point> body;
		Direction dir;
	public:
	        Snake(int startX, int startY);
	        void move();
		void changeDirection(Direction newDir);
		void grow();

		const std::vector<Point>& getBody() const { return body; }
		Point getHead() const { return body[0]; }
};

#endif
			       
