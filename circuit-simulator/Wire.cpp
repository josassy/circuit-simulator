#pragma once
#include "Wire.h"

Wire::Wire() {
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
}

void Wire::setState(WireValue state) {
  if (this->state != state) {
    for (Gate* gate : output) {
      gate->doLogic();
    }
  }
}

void Wire::doLogic() {
  history.push_back(state);
}
