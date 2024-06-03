#include <tuple>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H
namespace snk
{

  using Coord = std::tuple<int, int>;

  class Snake
  {
  public:
    Snake();
    Snake(int, int);
    void reset(int, int);
    void shift();
    void grow();
    int size();
    void replace_at(int, Coord);
    Coord get(int);
    void changeDir(int);
    int getDir();
    int getScore();

  private:
    std::vector<Coord> snake;
    int SNAKE_SIZE;
    int DIR;
    int score;
  };
}

#endif