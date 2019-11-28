#pragma once
#include <string>

enum GateType {
  AND,
  OR,
  XOR,
  NAND,
  NOR,
  XNOR,
  NOT
};

enum WireValue {
  ON = 1,
  OFF = 0,
  X = -1
};
