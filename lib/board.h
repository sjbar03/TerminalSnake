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
    void print();
    void reset();
    void placeSnake(snk::Snake);
    void placeFood();
    void start(listener::KeyListener *l);
    void checkFood();
    bool isRunning();
    void stop();
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