#include "food.h"
#include <vector>
#include <random>
#include <chrono>
#include <tuple>

using namespace food;

Food::Food() {}

Food::Food(int w, int h)
{
  boardW = w;
  boardH = h;
  reset();
  size = 0;
}

void Food::reset()
{
  foods.clear();
  size = 0;
}

void Food::spawnFood()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  int x = generator() % boardW;
  int y = generator() % boardH;

  Coord f = std::make_tuple(x, y);
  foods.push_back(f);
  size += 1;
}

Coord Food::get(int i)
{
  return foods.at(i);
}

void Food::rmFood(int i)
{
  foods.erase(foods.begin() + i);
  size -= 1;
}
