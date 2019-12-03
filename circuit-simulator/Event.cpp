#include "Event.h"

Event::Event(Wire* wire, int time, WireValue value, int count)
  : wire()
{
  this->wire = wire;
  this->time = time;
  this->value = value;
  this->count = count;
}

bool operator<(const Event & e1, const Event & e2)
{
  // Since a priority queue is ordered biggest to smallest, 
  // we want the event with lowest time to return biggest.
  // If events have same time, return first event created.
  if (e1.time == e2.time) {
    return e1.count > e2.count;
  }
  else {
    return e1.time > e2.time;
  }
}

void Event::print() const {
  std::cout << "wire " << wire->getName() << " to " << value << " at " << time << "ms. Event #" << count << std::endl;
}
