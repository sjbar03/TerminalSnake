#ifndef BOARD_H
#define BOARD_H

#include "snake.h"
#include "food.h"
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
    void step(int);
    void checkFood();

  private:
    snk::Snake s;
    food::Food f;
  };
  int height();
  int width();
}

#endif