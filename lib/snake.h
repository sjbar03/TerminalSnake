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

    /**
     * Create a new snake at the given coordinates.
     */
    Snake(int, int);

    /**
     * Empty snake body vector and reset to the provided coordinates.
     */
    void reset(int, int);

    /**
     * Logical shift right on snake body vector. Shift next position into
     * position zero, discard old last position.
     */
    void shift();

    /**
     * Increase the size of the snake vector by one.
     */
    void grow();

    /**
     * Return size of snake body vector.
     */
    int size();

    /**
     * Return the coordinates of the head of the snake.
     */
    Coord loc();

    /**
     * Return coordinate at specified position in snake.
     */
    Coord get(int);

    /**
     * Change direction of snake to provided direction.
     */
    void changeDir(int);

    /**
     * Return integer representation of snake's current direction.
     */
    int getDir();

    /**
     * Return current accumulated score.
     */
    int getScore();

  private:
    std::vector<Coord> snake;
    int SNAKE_SIZE;
    int DIR;
    int score;
  };
}

#endif