/*******************************************************************************
* File:       Event.h
* Name:       Josiah Lansford, Benjamin Harless
* Date:       4 December 2019
* Assignment: HW6 - Circuit Simulator
* Purpose:    Represents an event in the circuit simulation. Includes sorting
*             operator for use in priority queue, and print function
*******************************************************************************/
#pragma once

#include <iostream>
#include "Enums.h"
#include "Wire.h"
using namespace Enums;

class Event {
public: 
  //ctor
  Event(Wire* wire, int time, WireValue value, int count);
  
  // sort function for use in priority queue
  friend bool operator< (const Event& e1, const Event& e2);

  // debug statement to show event details
  void print() const;

  Wire* getWire() { return wire; }
  WireValue getWireValue() { return value; }
  int getTime() { return time; }

private:
  Wire* wire;
  int time; // in milliseconds
  WireValue value;
  int count; // keep track of order events were created
};