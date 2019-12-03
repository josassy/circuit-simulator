#pragma once
#include "Enums.h"
#include "Circuit.h"
using namespace Enums;

class Wire;

class Gate {
public:
  Gate(Circuit* circuit, GateType t, int d, Wire* i1, Wire* i2, Wire* o);
  Wire* getOut() const { return out; }
  int getDelay() const { return delay; }
  void eval();
  //void eval(WireValue state, Wire* input);

private:
  // store pointer to circuit for callbacks
  Circuit* circuit;
  WireValue doLogic(WireValue s1, WireValue s2);
  Wire* in1;
  Wire* in2;
  Wire* out;
  GateType type;
  int delay;
};