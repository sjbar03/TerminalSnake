#include "board.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ncurses.h>
using namespace brd;
using namespace std;

#define ONE_KEY 49
#define TWO_KEY 50
#define THREE_KEY 51
#define FOUR_KEY 52

#define Y_KEY 121
#define N_KEY 110

std::vector<string> split(const string &s, char delim)
{
  vector<string> result;
  stringstream ss(s);
  string item;

  while (getline(ss, item, delim))
  {
    result.push_back(item);
  }

  return result;
}

string getstring()
{

  string res;

  int ch = getch();

  while (ch != '\n')
  {
    res.push_back(ch);
    ch = getch();
  }

  return res;
}

void play()
{

  Board b = Board();

  b.start();

  printw("\nWould you like to save this score? y/n\n");
  nodelay(stdscr, false);

  bool answered = false;

  while (!answered)
  {
    switch (getch())
    {
    case (Y_KEY):
      nocbreak();
      echo();
      printw("Enter your username: ");
      b.recordScore(getstring());
      answered = true;
      break;
    case (N_KEY):
      answered = true;
      break;
    default:
      break;
    }
  }

  endwin();
}

void printRecord()
{
  clear();
  string line;

  ifstream scores("data/scores.csv");
  stringstream ss;

  while (getline(scores, line))
  {
    auto entry = split(line, ',');

    while (!entry.empty())
    {
      ss << setw(20) << left << entry.front();
      entry.erase(entry.begin());
    }
    ss << "\n";
  }
  scores.close();

  string s = ss.str();
  printw(s.c_str());
  getch();
}

string center(int w, string text)
{
  string res;

  int hw = w / 2;
  int ht = size(text) / 2;
  int padding = hw - ht;

  for (int i = 0; i < padding; ++i)
  {
    res += " ";
  }

  return res + text;
}

void printUsage()
{
  string line;
  ifstream help("data/help.txt");

  int i = 1;

  while (getline(help, line))
  {
    if (i < 10)
    {
      printw((center(80, line)).c_str());
    }
    else
    {
      printw(line.c_str());
    }
    printw("\n");
    refresh();
    i++;
  }
  getch();
  help.close();
  clear();
}

void menu()
{
  initscr();

  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_RED);

  cbreak();
  noecho();
  nodelay(stdscr, false);

  string line;
  ifstream logo("data/logo.txt");

  while (getline(logo, line))
  {
    printw((center(80, line)).c_str());
    printw("\n");
    refresh();
  }
  logo.close();

  switch (getch())
  {
  case ONE_KEY:
    clear();
    nodelay(stdscr, true);
    play();
    clear();
    nodelay(stdscr, false);
    menu();
    break;
  case TWO_KEY:
    clear();
    printRecord();
    clear();
    menu();
    break;
  case THREE_KEY:
    clear();
    printUsage();
    menu();
  case FOUR_KEY:
    break;
  default:
    clear();
    menu();
    break;
  }
  clear();
  endwin();
}

void test()
{
  initscr();
  cout << getch();
  endwin();
}

int main()
{
  // test();
  menu();
}