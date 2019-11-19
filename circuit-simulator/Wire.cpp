#pragma once
#include "Wire.h"

Wire::Wire() {
  // TODO
}

WireValue Wire::getState()
{
  return state;
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
