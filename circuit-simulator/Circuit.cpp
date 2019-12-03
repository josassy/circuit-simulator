#include "Circuit.h"

Circuit::Circuit(std::string name) 
  : name(name) {}

Wire* Circuit::getWire(int index) {
  if (wireArray.size >= index || wireArray.at(index) == nullptr) {
    Wire* newWire = new Wire();
    addWire(newWire, index);
  }
  return wireArray.at(index);
}

void Circuit::addWire(Wire* w, int index) {
  // If wireArray is wrong size, push back with nullptr
  while (wireArray.size <= index) {
    wireArray.push_back(nullptr);
  }

  // Add wire pointer to array
  wireArray.at(index) = w;
}

void Circuit::scheduleEvent(Event e) {
  eventQueue.push(e);
  eventCount++;
}

void Circuit::scheduleEvent(Wire* wire, WireValue value, int delay) {
  Event e = Event(wire, currTime + delay, value, eventCount);
  scheduleEvent(e);
}

void Circuit::processEvents() {
  while (eventQueue.size() > 0 || !processDone) {
    handleEvent(eventQueue.top());
  }
}

void Circuit::handleEvent(Event e) {
  // Print event details to debug
  e.print();

  // Set current time to event being processed
  currTime = e.getTime();

  // If a scheduled events time is more than 60 ms, stop processing
  if (e.getTime > 60) {
    processDone = true;
  }

  // Get pointer to target wire, and peform changes
  Wire* target = wireArray.at(e.getWireNum());
  target->setState(e.getWireValue());
}