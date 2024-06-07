#include "board.h"
#include "snake.h"
#include "food.h"
#include "keylistener.h"
#include <tuple>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace brd;
using namespace snk;
using namespace food;
using namespace listener;

#if defined(_WIN32) || defined(_WIN64)
#define _CLEAR system("cls")
#else
#define _CLEAR system("clear")
#endif

#define CHARACTER "||"

#define H 40
#define W 40

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int board[H][W];
vector<int> inputBuffer;

Board::Board()
{
  s = Snake(W / 2, H / 2);
  f = Food(W, H);
  iterations = 0;
  reset();
}

void Board::print()
{
  stringstream ss;

  ss << "\033[0m" << "Score: " << s.getScore() << '\n';

  for (int y = 0; y < H; ++y)
  {
    for (int x = 0; x < W; ++x)
    {
      if (board[y][x] == 1)
      {
        ss << "\033[30;40m" << CHARACTER;
      }
      else if (board[y][x] == 2)
      {
        ss << "\033[31;41m" << CHARACTER;
      }
      else
      {
        ss << "\033[37;47m" << CHARACTER;
      }
      ss << "\033[0m" << flush;
    }
    ss << '\n'
       << flush;
  }

  _CLEAR;
  cout << ss.str();
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

void Board::start(KeyListener *l)
{

  running = true;

  while (isRunning())
  {
    switch (l->pop())
    {
    case 'w':
      if (s.getDir() != SOUTH)
      {
        s.changeDir(NORTH);
      }
      break;
    case 'a':
      if (s.getDir() != EAST)
      {
        s.changeDir(WEST);
      }
      break;
    case 's':
      if (s.getDir() != NORTH)
      {
        s.changeDir(SOUTH);
      }
      break;
    case 'd':
      if (s.getDir() != WEST)
      {
        s.changeDir(EAST);
      }
      break;
    case 'p':
      while (l->isEmpty())
      {
        usleep(1000);
      }
      break;
    default:
      break;
    };
    s.shift();
    reset();
    if (iterations % 24 == 0)
    {
      f.spawnFood();
    }
    placeFood();
    placeSnake(s);
    checkFood();
    print();

    iterations += 1;
    usleep(100000);
  }
  cout << "\033[0m" << endl; // Change back to deafult color mode.
}

void Board::recordScore(string usr)
{
  int score = s.getScore();

  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  auto date = std::ctime(&time);

  ofstream scores("data/scores.csv", std::ios::app);

  if (!scores.is_open())
  {
    ofstream scores("data/scores.csv");
  }

  scores << usr << "," << score << "," << date;

  scores.close();
}
