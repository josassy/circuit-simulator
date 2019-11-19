#pragma once
#include "Wire.h"

enum GateType {
  AND,
  OR,
  XOR,
  NAND,
  NOR,
  XNOR,
  NOT
};

class Wire;

class Gate {
public:
  Gate();
  void doLogic();
  WireValue getNextOutput();

private:
  Wire* in1;
  Wire* in2;
  Wire* out;
  GateType type;
  int delay;
};