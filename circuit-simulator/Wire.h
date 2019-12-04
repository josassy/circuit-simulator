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
  void setState(WireValue state, int time = -1);

  Gate* getGate(int i) const { return output.at(i); }
  void setGate(Gate * g) { output.push_back(g); }
  int getNumGates() const { return (int)output.size(); }

  std::string getName() const { return name; }
  void setName(std::string name) { this->name = name; }

  void printHistory() const;

private:
  std::vector<Gate*> output; // All the gates that the wire drives
  std::vector<WireValue> history; // Full history of wire (including current state)
  std::string name;
};