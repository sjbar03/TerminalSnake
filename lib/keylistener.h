#ifndef KEY_LISTENER_H
#define KEY_LISTENER_H

#include <vector>
#include <mutex>

namespace listener
{
  class KeyListener
  {
  public:
    void start();
    void stop();
    void listen();

    void emptyQueue();
    void quitIf(char);

    bool isEmpty();
    bool isListening();

    char next();
    char pop();

  private:
    char quitCh;
    bool listening;
    std::vector<char> inputQueue;
    std::mutex queueLock;
  };
}

#endif