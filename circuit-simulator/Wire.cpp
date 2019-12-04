#pragma once

#include "Wire.h"
#include "Gate.h"

Wire::Wire(std::string name) {
  // Set passed in name to name prop
  this->name = name;
  
  // To begin, the wire's value will always be X
  history.push_back(WireValue::X);
}

WireValue Wire::getState() const
{
  // If no history, return unknown as we don't know state yet
  if (history.size() > 0) {
    return history.back();
  }
  else {
    return WireValue::X;
  }
}

WireValue Wire::getState(int time) const
{
  // check if index is valid. If not, call getState();
  if (time < history.size()) {
    return history.at(time);
  }
  else {
    return getState();
  }
}

void Wire::setState(WireValue state, int time) {
  //WireValue prevState = getState();

  // If time == -1, push to end of history
  if (time < 0) {
    history.push_back(state);
  }

  // If time == last index in history, change that
  else if (time == history.size() - 1) {
    history.back() = state;
  }

  // If time >= history.size, push to history
  else if (time >= history.size()) {
    // push back with existing state
    for (int i = history.size(); i < time; i++) {
      history.push_back(history.back());
    }
    // history.size should now == time
    history.push_back(state);
  }
}

void Wire::printHistory(int length) const {
  WireValue val;
  for (int i = 0; i < history.size(); i++) {
    val = history.at(i);
    std::cout << wireValToChar(val);
  }
  // If the desired length is greater than length of history,
  // print the last character enough times to fill the diff
  if (history.size() < length) {
    for (int i = 0; i < length - history.size(); i++) {
      std::cout << wireValToChar(history.back());
    }
  }
}
