#pragma once

class Event {
  int wireNum;
  int time;
  bool value;
  int count;

  friend bool operator< (const Event& e1, const Event& e2);
};