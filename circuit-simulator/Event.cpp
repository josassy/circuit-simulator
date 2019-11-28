#include "Event.h"

Event::Event(int wireNum, int time, WireValue value, int count) {
  this->wireNum = wireNum;
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

// Print function used for debugging
void Event::print() const {
  std::cout << "wire " << wireNum << " to " << value << " at " << time << "ms. Event #" << count << std::endl;
}
