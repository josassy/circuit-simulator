#pragma once
#include <vector>
#include <queue>
#include "Wire.h"
#include "Event.h"

class Circuit {
public:
  void scheduleEvent(Event e);
  void processEvents();

private:
  void handleEvent(Event e);
  // Hold the number of milliseconds we have processed
  bool processDone;
  std::vector<Wire*> wireArray;
  std::priority_queue<Event> eventQueue;
};