#include "board.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <ncurses.h>
using namespace brd;
using namespace std;

int main()
{
  initscr();

  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_RED);

  cbreak();
  noecho();
  nodelay(stdscr, true);

  Board b = Board();

  int iterations = 0;

  while (1)
  {
    b.step(iterations);

    usleep(2500);
    iterations += 1;
  }

  endwin();
}