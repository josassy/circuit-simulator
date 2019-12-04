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

std::string Enums::gateTypeToStr(GateType type)
{
  if (type == GateType::AND) { return "AND"; }
  if (type == GateType::OR) { return "OR"; }
  if (type == GateType::XOR) { return "XOR"; }
  if (type == GateType::NAND) { return "NAND"; }
  if (type == GateType::NOR) { return "NOR"; }
  if (type == GateType::XNOR) { return "XNOR"; }
  else { return "NOT"; }
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