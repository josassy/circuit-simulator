#pragma once

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

private:
  Wire* in1;
  Wire* in2;
  GateType type;
  int delay;
};