#include "board.h"
#include "snake.h"
#include "food.h"
#include <tuple>
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
using namespace brd;
using namespace snk;
using namespace food;
#define CHARACTER "||"

#define H 40
#define W 40

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

int board[H][W];

Board::Board()
{
  s = Snake(W / 2, H / 2);
  f = Food(W, H);
  iterations = 0;
  reset();
}

void Board::print()
{
  clear();
  for (int y = 0; y < H; ++y)
  {
    for (int x = 0; x < W; ++x)
    {
      if (board[y][x] == 1)
      {
        attron(COLOR_PAIR(1));
        printw(CHARACTER);
        attroff(COLOR_PAIR(1));
      }
      else if (board[y][x] == 2)
      {
        attron(COLOR_PAIR(3));
        printw(CHARACTER);
        attroff(COLOR_PAIR(3));
      }
      else
      {
        attron(COLOR_PAIR(2));
        printw(CHARACTER);
        attroff(COLOR_PAIR(2));
      }
    }
    printw("\n");
  }
}

void Board::reset()
{

  for (int x = 0; x < W; ++x)
  {
    for (int y = 0; y < H; ++y)
    {
      if (x == 0 or x == W - 1 or y == 0 or y == H - 1)
      {
        board[y][x] = 1;
      }
      else
      {
        board[y][x] = 0;
      }
    }
  }
}

void Board::placeSnake(Snake s)
{
  for (int i = 0; i < s.size(); ++i)
  {
    int x = get<0>(s.get(i));
    int y = get<1>(s.get(i));
    if (board[y][x] == 1)
    {
      cout << "Hit\n";
      stop();
    }
    board[y][x] = 1;
  }
}

void Board::stop()
{
  running = false;
}

int height()
{
  return H;
}

int width()
{
  return W;
}

void Board::placeFood()
{
  for (int i = 0; i < f.size; ++i)
  {
    Coord c = f.get(i);
    int x = get<0>(c);
    int y = get<1>(c);
    if (board[y][x] == 1)
    {
      continue;
    }
    else
    {
      board[y][x] = 2;
    }
  }
}

void Board::checkFood()
{
  Coord scoord = s.get(0);
  int sx = get<0>(scoord);
  int sy = get<1>(scoord);

  for (int i = 0; i < f.size; ++i)
  {
    Coord fcoord = f.get(i);
    int fx = get<0>(fcoord);
    int fy = get<1>(fcoord);

    if (fx == sx && fy == sy)
    {
      s.grow();
      f.rmFood(i);
    }
  }
}

bool Board::isRunning()
{
  return running;
}

void Board::start()
{
  running = true;

  while (isRunning())
  {
    switch (getch())
    {
    case W_KEY:
      if (s.getDir() != SOUTH)
      {
        s.changeDir(NORTH);
      }
      break;
    case A_KEY:
      if (s.getDir() != EAST)
      {
        s.changeDir(WEST);
      }
      break;
    case S_KEY:
      if (s.getDir() != NORTH)
      {
        s.changeDir(SOUTH);
      }
      break;
    case D_KEY:
      if (s.getDir() != WEST)
      {
        s.changeDir(EAST);
      }
      break;
    default:
      break;
    };

    if (iterations % 40 == 0)
    {
      s.shift();
      reset();
      if (iterations % 800 == 0)
      {
        f.spawnFood();
      }
      placeFood();
      placeSnake(s);
      checkFood();
      print();
      refresh();
    }

    iterations += 1;
    usleep(2500);
  }
}