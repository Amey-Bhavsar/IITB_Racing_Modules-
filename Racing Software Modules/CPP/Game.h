#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "Snake.h"
#include "Food.h"

class Game {
	private:
		Snake snake;
		Food food;
		int width, height;
		int score;
		bool gameOver;
	public:
		Game();
		~Game();

		void setup();
		void draw();
		void handleInput();
		void update();
		bool isOver() const { return gameOver;}
		int getScore() const { return score;}

		void run();
};

#endif
