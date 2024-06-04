#ifndef KEY_LISTENER_H
#define KEY_LISTENER_H

#include <vector>
#include <mutex>

namespace listener
{
  class KeyListener
  {
  public:
    void start(int);
    void stop(std::thread *);

    void listen(int);

    bool isEmpty();
    bool isListening();
    char pop();

  private:
    bool listening;
    std::vector<char> inputQueue;
    std::mutex queueLock;
  };
}

#endif