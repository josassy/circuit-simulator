#pragma once
#include <vector>
#include <queue>
#include "Wire.h"
#include "Event.h"

class Circuit {

private:
  std::vector<Wire*> wireArray;
  std::priority_queue<Event> eventQueue;
};