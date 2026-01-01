#include "Game.h"
#include <unistd.h> // For usleep()

Game::Game() : snake(10, 10), food(40, 20) {
    width = 40;
    height = 40;
    score = 0;
    gameOver = false;

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);          // Hide the blinking cursor
    keypad(stdscr, TRUE); // Enable arrow keys
    nodelay(stdscr, TRUE); // Don't wait for user input (real-time)
}

Game::~Game() {
    endwin(); // Clean up ncurses when the game is done
}

void Game::draw() {
    erase(); // Clear the screen

    // Draw the Border
    for (int i = 0; i < width; i++) mvaddch(0, i, '#');          // Top
    for (int i = 0; i < width; i++) mvaddch(height - 1, i, '#'); // Bottom
    for (int i = 0; i < height; i++) mvaddch(i, 0, '#');         // Left
    for (int i = 0; i < height; i++) mvaddch(i, width - 1, '#'); // Right

    // Draw the Food
    mvaddch(food.getPos().y, food.getPos().x, '*');

    // Draw the Snake
    const auto& body = snake.getBody();
    for (size_t i = 0; i < body.size(); i++) {
        // Draw head as 'O', body as 'o'
        mvaddch(body[i].y, body[i].x, (i == 0) ? 'O' : 'o');
    }

    // Draw Score
    mvprintw(0, width + 2, "Score: %d", score);
    
    refresh();
}

void Game::handleInput() {
    int ch = getch(); // Get user keyboard input
    switch (ch) {
        case KEY_UP:    case 'w': snake.changeDirection(UP);    break;
        case KEY_DOWN:  case 's': snake.changeDirection(DOWN);  break;
        case KEY_LEFT:  case 'a': snake.changeDirection(LEFT);  break;
        case KEY_RIGHT: case 'd': snake.changeDirection(RIGHT); break;
        case 'q':                 gameOver = true;              break;
    }
}

void Game::update() {
    snake.move();
    Point head = snake.getHead();

    // Check Food Collision
    if (head.x == food.getPos().x && head.y == food.getPos().y) {
        score += 10;
        snake.grow();
        food.respawn();
    }

    // Check Wall Collision
    if (head.x <= 0 || head.x >= width - 1 || head.y <= 0 || head.y >= height - 1) {
        gameOver = true;
    }

    // Check Self Collision
    const auto& body = snake.getBody();
    for (size_t i = 1; i < body.size(); i++) {
        if (head.x == body[i].x && head.y == body[i].y) {
            gameOver = true;
        }
    }
}

void Game::run() {
    while (!gameOver) {
        draw();
        handleInput();
        update();
        usleep(100000); // Control game speed (100ms)
    }
    
    // Game Over Screen
    nodelay(stdscr, FALSE); // Wait for user to press a key before closing
    mvprintw(height/2, width/4, "GAME OVER! Score: %d", score);
    mvprintw(height/2 + 1, width/4, "Press any key to quit...");
    getch();
}
