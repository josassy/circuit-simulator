#pragma once
#include <vector>
#include <queue>
#include "Wire.h"
#include "Gate.h"
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
  * Get the wire with a specified name.
  * If none exists, will return nullptr.
  */
  Wire* getWire(std::string name);
  
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
  
 /**
  * Iterate through each Event in eventQueue,
  * processing them and causing the affected Gates
  * to generate new Events as needed
  * This function will process until (processDone)
  * or all events are processed
  */
  void processEvents();

 /**
  * WARNING: This method is destructive and will empty the event queue.
  * Used for debugging purposes.
  * Prints all the events in the queue.
  */
  void printEvents();

 /**
  * Print the full history of each wire in Circuit.
  * Should be called after processEvents().
  */
  void printHistory() const;

 /**
  * Print summary of Wires and Gates in circuit
  * Used for debugging purposes
  */
  void printSummary() const;

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