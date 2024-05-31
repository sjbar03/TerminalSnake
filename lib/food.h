#ifndef FOOD_H
#define FOOD_H

#include <tuple>
#include <vector>

namespace food
{
  using Coord = std::tuple<int, int>;
  class Food
  {
  public:
    Food();
    Food(int, int);
    std::vector<Coord> foods;
    void reset();
    void spawnFood();
    void rmFood(int);
    Coord get(int);
    int size;

  private:
    int boardW;
    int boardH;
  };

}

#endif