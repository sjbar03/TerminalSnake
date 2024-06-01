#include "board.h"

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

  b.start();

  endwin();
}