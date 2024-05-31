#include <tuple>

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

  private:
    Coord snake[500];
    int SNAKE_SIZE = 1;
    int DIR = 0;
  };
}

#endif