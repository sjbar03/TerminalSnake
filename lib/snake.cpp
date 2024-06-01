#include "snake.h"
#include <tuple>
using namespace snk;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Snake::Snake() {}

Snake::Snake(int x, int y)
{
  reset(x, y);
}

void Snake::reset(int x, int y)
{
  SNAKE_SIZE = 1;
  snake.clear();
  snake.insert(snake.begin(), std::make_tuple(x, y));
}

void Snake::grow()
{
  SNAKE_SIZE += 1;
}

void Snake::shift()
{

  Coord currpos = snake[0];
  int currx = std::get<0>(currpos);
  int curry = std::get<1>(currpos);

  Coord next;
  switch (DIR)
  {
  case NORTH:
    next = std::make_tuple(currx, curry - 1);
    break;
  case EAST:
    next = std::make_tuple(currx + 1, curry);
    break;
  case SOUTH:
    next = std::make_tuple(currx, curry + 1);
    break;
  case WEST:
    next = std::make_tuple(currx - 1, curry);
    break;
  default:
    next = currpos;
    break;
  };

  for (int i = SNAKE_SIZE - 1; i >= 0; --i)
  {
    if (i == 0)
    {
      snake[i] = next;
    }
    else
    {
      if (i == SNAKE_SIZE - 1 && SNAKE_SIZE > snake.size())
      {
        snake.push_back(snake[i - 1]);
      }
      snake[i] = snake[i - 1];
    }
  }
}

int Snake::size()
{
  return SNAKE_SIZE;
}

void Snake::replace_at(int i, Coord c)
{
  snake[i] = c;
}

Coord Snake::get(int i)
{
  return snake[i];
}

void Snake::changeDir(int d)
{
  DIR = d;
}

int Snake::getDir()
{
  return DIR;
}