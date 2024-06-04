#include "keylistener.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

using namespace listener;

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>

// Function to get unbuffered input on Windows
char get_unbuffered_input()
{
  return _getch();
}

#else
#include <unistd.h>
#include <termios.h>

// Function to set terminal to unbuffered mode
void set_unbuffered_mode(termios &old_term)
{
  termios new_term = old_term;
  new_term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

// Function to reset terminal to its original mode
void reset_terminal_mode(termios &old_term)
{
  tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

// Function to get unbuffered input on Unix-based systems
char get_unbuffered_input()
{
  char ch;
  termios old_term;

  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &old_term);

  // Set terminal to unbuffered mode
  set_unbuffered_mode(old_term);

  // Read a single character
  read(STDIN_FILENO, &ch, 1);

  // Reset terminal to original mode
  reset_terminal_mode(old_term);

  return ch;
}

void KeyListener::start(int id)
{
  listening = true;
  listen(id);
}

void KeyListener::stop(std::thread *pt)
{
  listening = false;
  (*pt).join();
}

void KeyListener::listen(int tId)
{
  std::cout << "Reached listen() on thread: " << tId << std::endl;
  while (isListening())
  {
    char ch = get_unbuffered_input();
    queueLock.lock();
    inputQueue.push_back(ch);
    queueLock.unlock();
  }
}

bool KeyListener::isEmpty()
{
  return inputQueue.empty();
}

bool KeyListener::isListening()
{
  return listening;
}

char KeyListener::pop()
{
  char ch;
  queueLock.lock();
  if (!isEmpty())
  {
    ch = inputQueue.front();
    inputQueue.erase(inputQueue.begin());
  }
  queueLock.unlock();

  return ch;
}

#endif