#include "Circuit.h"

void Circuit::scheduleEvent(Event e) {
  eventQueue.push(e);
}

void Circuit::processEvents() {
  while (eventQueue.size() > 0 || !processDone) {
    handleEvent(eventQueue.top());
  }
}

void Circuit::handleEvent(Event e) {
  // Print event details to debug
  e.print();

  // If a scheduled events time is more than 60 ms, stop processing
  if (e.getTime > 60) {
    processDone = true;
  }

  // Get pointer to target wire, and peform changes
  Wire* target = wireArray.at(e.getWireNum());
  target->setState(e.getWireValue());
}