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
  std::string gateTypeToStr(GateType type);

/**
 * Convert char to WireValue
 * @param {char} c char to convert to WireValue
 * @return {WireValue} WireValue representation of char
 */
  WireValue charToWireVal(char c);

/**
 * Convert WireValue to char
 * @param {WireValue} val WireValue to convert
 * @return {char} char representation of WireValue
 */
  char wireValToChar(WireValue val);
}
