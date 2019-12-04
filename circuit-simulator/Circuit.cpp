#include "Circuit.h"

Circuit::Circuit(std::string name) 
  : name(name) {
  currTime = 0;
  eventCount = 0;
  processDone = false;
}

Wire* Circuit::getWire(int index) {
  if (wireArray.size() <= index || wireArray.at(index) == nullptr) {
    Wire* newWire = new Wire();
    addWire(newWire, index);
  }
  return wireArray.at(index);
}

Wire* Circuit::getWire(std::string name) {
  for (Wire* wire : wireArray) {
    if (wire != nullptr && wire->getName() == name) {
      return wire;
    }
  }
  return nullptr;
}

void Circuit::addWire(Wire* w, int index) {
  // If wireArray is wrong size, push back with nullptr
  while (wireArray.size() <= index) {
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
  if (e.getTime() > 60) {
    processDone = true;
    return;
  }

  WireValue value = e.getWireValue();
  Wire* target = e.getWire();
  
  // Use pointer to target wire to peform changes
  target->setState(value);

  // Check if change in wire will change a downstream gate's output
  for (int i = 0; i < target->getNumGates(); i++) {
    Gate* gate = target->getGate(i);
    WireValue prevValue = gate->getOut()->getState();
    WireValue currValue = gate->eval(value, target);

    // If output should change, schedule event to update gate's output
    if (currValue != prevValue) {
      scheduleEvent(gate->getOut(), currValue, gate->getDelay());
    }
  }
}

void Circuit::printEvents() {
  int size = eventQueue.size();
  for (int i = 0; i < size; i++) {
    eventQueue.top().print();
    eventQueue.pop();
  }
}

void Circuit::printWires() const {
  std::cout << "Circuit name: " << name << std::endl;
  for (Wire* wire : wireArray) {
    // We only want to print the wires that have names
    if (wire != nullptr && wire->getName() != "") {
      std::cout << wire->getName() << ':\t';
      wire->printHistory();
      std::cout << std::endl;
    }
  }
}

void Circuit::printSummary() const {
  std::cout << "Circuit name: " << name << std::endl;
  for (Wire* wire : wireArray) {
    if (wire != nullptr) {
      std::cout << "Wire name: " << wire->getName();
      int numGates = wire->getNumGates();
      std::cout << " Feeds " << numGates << " gates, ";

      // Loop through each gate on the wire, printing its type
      for (int i = 0; i < numGates; i++) {
        std::cout << gateTypeToStr(wire->getGate(i)->getType());
      }

      std::cout << std::endl;
    }
  }
}