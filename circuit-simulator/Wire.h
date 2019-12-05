/*******************************************************************************
* File:       Wire.h
* Name:       Josiah Lansford, Benjamin Harless
* Date:       4 December 2019
* Assignment: HW6 - Circuit Simulator
* Purpose:    
*******************************************************************************/
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Enums.h"

using namespace Enums;

class Gate;

class Wire {
public:
  Wire(std::string name = "");
  WireValue getState() const;
  WireValue getState(int time) const;

 /**
  * Set the state of the wire
  * @param {WireValue} state the value to set wire to
  * @param {int}       time  the time in history the
  * change should be made. Can be equal to or more than
  * current time. If time is equal, it will replace the
  * current history value rather than push_back(state)
  */
  void setState(WireValue state, int time = -1);

  Gate* getGate(int i) const { return output.at(i); }
  void setGate(Gate * g) { output.push_back(g); }
  int getNumGates() const { return (int)output.size(); }

  std::string getName() const { return name; }
  void setName(std::string name) { this->name = name; }

 /**
  * Print the full history of the wire.
  * @param {int} length Desired length of history, if more than actual history.
  * If desired length is greater than history length, it will print the last
  * value in the history to fill the difference
  */
  void printHistory(int length = -1) const;

private:
  std::vector<Gate*> output; // All the gates that the wire drives
  std::vector<WireValue> history; // Full history of wire (including current state)
  std::string name;
};