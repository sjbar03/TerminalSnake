#ifndef BOARD_H
#define BOARD_H

#include "snake.h"
#include "food.h"
#include "keylistener.h"
#include <tuple>

namespace brd
{
  class Board
  {
  public:
    Board();

    /**
     * Print board.
     */
    void print();

    /**
     * Reset board, set all center blocks to white and edge blocks to black.
     */
    void reset();

    /**
     * Iterate over snake, flip each corresponding coordinate to black to
     * display snake.
     */
    void placeSnake(snk::Snake);

    /**
     * Check if the snakes next position will collide with something,
     * ends the game if so. Reccomended to call this before snake.shift();
     */
    void checkHit(snk::Snake);

    /**
     * Iterate over food and place each in the graphics array.
     */
    void placeFood();

    /**
     * Start the graphics loop with the provided keylistener.
     */
    void start(listener::KeyListener *);

    /**
     * Check if snake has collided with food. Determine whether or not to
     * grow, and modify food object.
     */
    void checkFood();

    /**
     * Retrieve status of game.
     */
    bool isRunning();

    /**
     * Set running to false (Game will end after next loop).
     */
    void stop();

    /**
     * Place acquired score in the score file with provided username.
     */
    void recordScore(std::string);

  private:
    int iterations;
    bool running;
    snk::Snake s;
    food::Food f;
  };
  int height();
  int width();
}

#endif