/*******************************************************************************
* File:       Circuit.cpp
* Name:       Josiah Lansford, Benjamin Harless
* Date:       4 December 2019
* Assignment: HW6 - Circuit Simulator
* Purpose:    Reperesents the logic circuit as a collection of Wires, Gates,
*             and Events, and runs the simulation.
*******************************************************************************/
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

void Circuit::processEvents(bool verbose) {
  while (eventQueue.size() > 0 && !processDone) {
    // Print event details to debug 
    if (verbose) {
      eventQueue.top().print();
    }
    handleEvent(eventQueue.top());
    eventQueue.pop();
  }
}

void Circuit::handleEvent(Event e) {

  WireValue value = e.getWireValue();
  Wire* target = e.getWire();

  // If the event's effects have already happened, ignore the event
  if (target->getState() == value) {
    return;
  }

  // If a scheduled events time is more than 60 ms, stop processing
  if (e.getTime() > 60) {
    processDone = true;
    return;
  }

  // Set current time to event being processed
  currTime = e.getTime();

  // Check if change in wire will change a downstream gate's output
  for (int i = 0; i < target->getNumGates(); i++) {
    Gate* gate = target->getGate(i);

    // Get WireValue as the inputs currently stand
    WireValue currValue = gate->eval();

    // Get wire value if the target input were to change state to value
    WireValue futureValue = gate->eval(value, target);

    // If gate output will change, schedule event to update gate's output
    if (currValue != futureValue) {
      scheduleEvent(gate->getOut(), futureValue, gate->getDelay());
    }
  }
  
  // Use pointer to target wire to peform changes
  target->setState(value, currTime);
}

void Circuit::printEvents() {
  int size = eventQueue.size();
  for (int i = 0; i < size; i++) {
    eventQueue.top().print();
    eventQueue.pop();
  }
}

void Circuit::printHistory() const {
  std::cout << "Circuit name: " << name << std::endl;
  for (Wire* wire : wireArray) {
    // We only want to print the wires that have names
    if (wire != nullptr && wire->getName() != "") {
      std::cout << wire->getName() << ":\t";
      wire->printHistory(currTime + 1);
      std::cout << "\n\n";
    }
  }

  // Print numbers to indicate time
  std::cout << "\t";
  for (int i = 0; i < currTime; i++) {
    if (i % 5 == 0) {
      std::cout << i % 10;
    }
    else {
      std::cout << ' ';
    }
  }

  // always print last history
  std::cout << currTime;
  std::cout << std::endl;
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
        Gate* gate = wire->getGate(i);
        std::cout << gateTypeToStr(gate->getType()) << " (" << 
          gate->getDelay() << "ms)";
      }

      std::cout << std::endl;
    }
  }
}