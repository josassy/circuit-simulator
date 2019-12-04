#pragma once

#include "Gate.h"
#include "Circuit.h"
#include "Wire.h"

Gate::Gate(GateType t, int d, Wire* i1, Wire* i2, Wire* o)
  : type(t), delay(d), in1(i1), in2(i2), out(o) 
{}

WireValue Gate::eval()
{
  // Handle special case of NOT gate
  if (type == GateType::NOT) {
    return doLogic(in1->getState(), WireValue::X);
  }
  return doLogic(in1->getState(), in2->getState());
}

WireValue Gate::doLogic(WireValue in1State, WireValue in2State)
{
  switch (type) {
  case GateType::AND:
    if (in1State == 0 || in2State == 0) {
      return WireValue::OFF;
      break;
    }
    else if (in1State == WireValue::X || in2State == WireValue::X) {
      return WireValue::X;
      break;
    }
    else {
      return WireValue::ON;
      break;
    }
  case GateType::OR:
    if (in1State == 1 || in2State == 1) {
      return WireValue::ON;
      break;
    }
    else if (in1State == -1 || in2State == -1) {
      return WireValue::X;
      break;
    }
    else {
      return WireValue::OFF;
      break;
    }
  case GateType::XOR:
    if (in1State == -1 || in2State == -1) {
      return WireValue::X;
      break;
    }
    else if (in1State == in2State) {
      return WireValue::OFF;
      break;
    }
    else {
      return WireValue::ON;
      break;
    }
  case GateType::NAND:
    if (in1State == 0 || in2State == 0) {
      return WireValue::ON;
      break;
    }
    else if (in1State == WireValue::X || in2State == WireValue::X) {
      return WireValue::X;
      break;
    }
    else {
      return WireValue::OFF;
      break;
    }
  case GateType::NOR:
    if (in1State == 1 || in2State == 1) {
      return WireValue::OFF;
      break;
    }
    else if (in1State == -1 || in2State == -1) {
      return WireValue::X;
      break;
    }
    else {
      return WireValue::ON;
      break;
    }
  case GateType::XNOR:
    if (in1State == -1 || in2State == -1) {
      return WireValue::X;
      break;
    }
    else if (in1State == in2State) {
      return WireValue::ON;
      break;
    }
    else {
      return WireValue::OFF;
      break;
    }
  case GateType::NOT:
    if (in1State == -1) {
      return WireValue::X;
      break;
    }
    else if (in1State == 1) {
      return WireValue::OFF;
      break;
    }
    else {
      return WireValue::ON;
      break;
    }
  }
}
