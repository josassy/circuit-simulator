#pragma once
#include "Enums.h"
using namespace Enums;

class Wire;

class Gate {
public:
  Gate(GateType t, int d, Wire* i1, Wire* i2, Wire* o);
  WireValue eval();
  WireValue eval(WireValue state, Wire* input);
  Wire* getOut() const { return out; }
  int getDelay() const { return delay; }

private:
  WireValue doLogic(WireValue s1, WireValue s2);
  Wire* in1;
  Wire* in2;
  Wire* out;
  GateType type;
  int delay;
};