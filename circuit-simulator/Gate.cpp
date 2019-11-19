#pragma once

#include "Gate.h"

Gate::Gate() {
  // TODO
}

void Gate::doLogic() {
  if (getNextOutput() != out->getState()) {
    // TODO: Logic to schedule change event
  }
}

WireValue Gate::getNextOutput() {
  WireValue in1State; 
  WireValue in2State;
  in1State = in1->getState();
  // In case NOT gate, don't get in2 state
  if (type != GateType::NOT) {
    in2State = in2->getState();
  }

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
