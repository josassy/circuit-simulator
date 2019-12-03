#pragma once
#include <vector>
#include <queue>
#include "Wire.h"
#include "Event.h"

class Circuit {
public:
  
 /**
  * Constructor
  * @param {string} name (optional) the name of the circuit
  */
  Circuit(std::string name = "");

 /**
  * Get the wire at specified index. 
  * If none exists, create one and return it
  */ 
  Wire* getWire(int index);
  
 /**
  * Add an event to the eventQueue.
  */
  void scheduleEvent(Event e);

/**
  * Add an event to the eventQueue by props
  * Creates new Event based on current "time"
  * @param {int} wireNum the wire being changed
  * @param {WireValue} value the target value
  * @param {int} delay gate delay of event
  */
  void scheduleEvent(Wire* wire, WireValue value, int delay);
  void processEvents();

private:
  int currTime;
  int eventCount;
  std::string name;
  void addWire(Wire* w, int index);
  void handleEvent(Event e);
  // Hold the number of milliseconds we have processed
  bool processDone;
  std::vector<Wire*> wireArray;
  std::priority_queue<Event> eventQueue;
};