#pragma once
#include "Wire.h"
#include "Gate.h"

Wire::Wire(WireValue s) {
  // TODO
}

WireValue Wire::getState()
{
  // TODO: check if history size is more than 0
  return history.back();
}

WireValue Wire::getState(int time)
{
  // check if index is valid. If not, call getState();
  return WireValue::X;
}

void Wire::setState(WireValue state) {
  if (this->getState() != state) {
    for (int i = 0; i < getNumGates(); i++) {
      getGate(i)->eval();
    }
  }
}
