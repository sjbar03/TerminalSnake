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

// Character for graphics
#define CHARACTER "||"

// Board dimensions
#define H 40
#define W 40

// SNAKE directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// ANSI color codes
#define WHITE "\033[37;47m"
#define BLACK "\033[30;40m"
#define RED "\033[31;41m"
#define _DEFAULT "\033[0m"

// ANSI position codes
#define HOME "\033[H"

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
  cout << HOME;

  stringstream ss;

  ss << _DEFAULT << "Score: " << s.getScore() << '\n';

  for (int y = 0; y < H; ++y)
  {
    for (int x = 0; x < W; ++x)
    {
      if (board[y][x] == 1)
      {
        ss << BLACK << CHARACTER;
      }
      else if (board[y][x] == 2)
      {
        ss << RED << CHARACTER;
      }
      else
      {
        ss << WHITE << CHARACTER;
      }
      ss << _DEFAULT << flush;
    }
    ss << '\n'
       << flush;
  }

  cout << ss.str() << flush;
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
    board[y][x] = 1;
  }
}

void Board::checkHit(Snake s)
{
  Coord currPos = s.loc();
  int currx = get<0>(currPos);
  int curry = get<1>(currPos);

  switch (s.getDir())
  {
  case (NORTH):
    if (board[curry - 1][currx] == 1)
    {
      stop();
    }
    break;
  case (EAST):
    if (board[curry][currx + 1] == 1)
    {
      stop();
    }
    break;
  case (SOUTH):
    if (board[curry + 1][currx] == 1)
    {
      stop();
    }
    break;
  case (WEST):
    if (board[curry][currx - 1] == 1)
    {
      stop();
    }
    break;
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
    checkHit(s);
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
  cout << _DEFAULT << endl; // Change back to deafult color mode.
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
