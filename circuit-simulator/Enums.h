#pragma once
#include <string>

/*
* Namespace to hold all the enums
*/
namespace Enums {

  // Represent valid type of logic gate
  enum GateType {
    AND,
    OR,
    XOR,
    NAND,
    NOR,
    XNOR,
    NOT
  };

  // Represent valid gate value
  enum WireValue {
    ON = 1,
    OFF = 0,
    X = -1
  };

  GateType strToGateType(std::string str);
}
