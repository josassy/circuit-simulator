#pragma once

#include <vector>
#include <string>
#include "Enums.h"

class Gate;

class Wire {
public:
  Wire(WireValue s = WireValue::X);
  WireValue getState();
  WireValue getState(int time);
  void setState(WireValue state);

  Gate* getGate(int i) const { return output[i]; }
  void setGate(Gate * g) { output.push_back(g); }
  int getNumGates() const { return (int)output.size(); }


private:
  std::vector<Gate*> output; // All the gates that the wire drives
  std::vector<WireValue> history; // Full history of wire (including current state)
  std::string name;
};