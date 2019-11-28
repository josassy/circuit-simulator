#include <iostream>
#include <queue>
#include "Event.h"
#include "Enums.h"

using namespace Enums;

int main() {
  std::cout << "Hello World!" << std::endl;
  
  std::priority_queue<Event> queue;
  queue.push(*new Event(2, 3, WireValue::OFF, 0));
  queue.push(*new Event(1, 4, WireValue::OFF, 1));
  queue.push(*new Event(4, 16, WireValue::OFF, 2));
  queue.push(*new Event(2, 1, WireValue::OFF, 3));
  queue.push(*new Event(2, 3, WireValue::OFF, 4));
  queue.push(*new Event(2, 3, WireValue::OFF, 5));

  int size = queue.size();
  for (int i = 0; i < size; i++) {
    queue.top().print();
    queue.pop();
  }

  int a;
  std::cin >> a;
  
  return 0;
}