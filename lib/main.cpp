#include "board.h"
#include "keylistener.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace brd;
using namespace std;
using namespace listener;

#if defined(_WIN32) || defined(_WIN64)
#define _CLEAR system("cls")
#else
#define _CLEAR system("clear")
#endif

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

void play(KeyListener *l)
{
  Board b = Board();
  b.start(l);

  cout << "Would you like to save your score? y/n" << endl;
  bool answered = false;

  string usr;
  while (!answered)
  {
    l->emptyQueue();
    l->pause();
    usleep(5000);
    cout << '\r';
    switch (l->pop())
    {
    case 'y':
      cout << "Please enter your username" << endl;
      cin >> usr;
      b.recordScore(usr);
      answered = true;
      break;
    case 'n':
      answered = true;
      break;
    default:
      break;
    }
    l->unpause();
    usleep(5000);
  }
}

bool compareEntry(vector<string> e1, vector<string> e2)
{
  int e1s = stoi(e1.at(1));
  int e2s = stoi(e2.at(1));
  return e1s > e2s;
}

void printRecord(KeyListener *l)
{
  _CLEAR;
  string line;

  ifstream scores("data/scores.csv");
  stringstream ss;

  vector<vector<string>> entries;

  while (getline(scores, line))
  {
    auto entry = split(line, ',');
    entries.push_back(entry);
  }

  sort(entries.begin() + 1, entries.end(), compareEntry); // Skip first line for header

  while (!entries.empty())
  {
    auto entry = entries.front();
    entries.erase(entries.begin());
    while (!entry.empty())
    {
      ss << setw(20) << left << entry.front();
      entry.erase(entry.begin());
    }
    ss << "\n";
  }
  scores.close();

  string s = ss.str();
  cout << s;
  l->emptyQueue();
  while (l->isEmpty())
  {
    usleep(1000);
  }
  _CLEAR;
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

void printUsage(KeyListener *l)
{
  string line;
  ifstream help("data/help.txt");

  int i = 1;

  while (getline(help, line))
  {
    if (i < 10)
    {
      cout << ((center(80, line)).c_str());
    }
    else
    {
      cout << (line.c_str());
    }
    cout << ("\n");
    i++;
  }

  help.close();
  l->emptyQueue();
  while (l->isEmpty())
  {
    usleep(1000);
  }
  _CLEAR;
}

void menu(KeyListener *l)
{
  string line;
  ifstream logo("data/logo.txt");

  while (getline(logo, line))
  {
    cout << (line.c_str());
    cout << '\n';
  }
  logo.close();

  l->quitIf('4');

  switch (l->pop())
  {
  case '1':
    _CLEAR;
    l->quitIf(-1);
    play(l);
    _CLEAR;
    menu(l);
    break;
  case '2':
    _CLEAR;
    l->quitIf(-1);
    printRecord(l);
    _CLEAR;
    menu(l);
    break;
  case '3':
    _CLEAR;
    l->quitIf(-1);
    printUsage(l);
    menu(l);
  case '4':
    l->stop();
    break;
  default:
    usleep(40000);
    _CLEAR;
    menu(l);
    break;
  }
  _CLEAR;
}

int main()
{
  KeyListener l = KeyListener();

  thread worker = thread(&menu, &l);

  l.start();

  worker.join();
}