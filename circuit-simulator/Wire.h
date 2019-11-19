#pragma once

#include <vector>
#include <string>
#include "Gate.h"

enum WireValue {
  ON = 1,
  OFF = 0,
  X = -1
};

class Gate;

class Wire {
public:
  Wire();
  WireValue getState();
  void setState(WireValue state);
  void doLogic();

private:
  std::vector<Gate*> output;
  WireValue state;
  std::vector<WireValue> history;
  std::string name;
};