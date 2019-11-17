#pragma once

#include <vector>
#include <string>

enum WireValue {
  ON,
  OFF,
  X
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
  int WireNum;
  std::string name;
};