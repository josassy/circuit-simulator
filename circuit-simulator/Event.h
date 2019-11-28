#pragma once

#include <iostream>
#include "Enums.h"
using namespace Enums;

class Event {
public: 
  //ctor
  Event(int wireNum, int time, WireValue value, int count);
  friend bool operator< (const Event& e1, const Event& e2);
  void print() const;

private:
  int wireNum;
  int time; // in milliseconds
  WireValue value;
  int count; // keep track of order events were created
};