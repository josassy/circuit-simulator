#pragma once

#include <vector>
#include <string>

enum WireValue {
  ON = 1,
  OFF = 0,
  X = -1
};

class Gate;

class Wire {
public:
  Wire();
  void doLogic();

private:
  std::vector<Gate*> out;
  WireValue state;
  std::vector<WireValue> history;
  std::string name;
};