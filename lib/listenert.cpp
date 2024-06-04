#include "keylistener.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

void printloop(listener::KeyListener *l)
{
  while (l->isListening())
  {
    if (!l->isEmpty())
    {
      std::cout << l->pop() << std::endl;
    }
    usleep(10000);
  }
}

int main()
{
  listener::KeyListener l = listener::KeyListener();

  std::thread worker = std::thread(&printloop, &l);

  l.start(1);

  l.stop(&worker);
}