#pragma once
#include <string>

namespace Enums {
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

  GateType strToGateType(std::string str);
}
