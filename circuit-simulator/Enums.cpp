#pragma once
#include "Enums.h"

using namespace Enums;

/**
 * Convert string input to GateType.
 * Assumes valid input of one of the enums, returns NOT by default.
 */
GateType Enums::strToGateType(std::string str) {
  if (str == "AND") { return GateType::AND; }
  else if (str == "OR") { return GateType::OR; }
  else if (str == "XOR") { return GateType::XOR; }
  else if (str == "NAND") { return GateType::NAND; }
  else if (str == "NOR") { return GateType::NOR; }
  else if (str == "XNOR") { return GateType::XNOR; }
  else if (str == "NOT") { return GateType::NOT; }
  else { throw std::exception("invalid gate type"); }
}

/**
 * Convert WireValue to char
 * @param {WireValue} val WireValue to convert
 * @return {char} char representation of WireValue
 */
char Enums::wireValToChar(WireValue val) {
  switch (val) {
  case WireValue::OFF:
    return '_';
    break;
  case WireValue::ON:
    return '-';
    break;
  case WireValue::X:
  default:
    return 'X';
    break;
  }
}