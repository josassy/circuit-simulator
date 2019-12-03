#include <iostream>
#include <queue>
#include "Event.h"
#include "Enums.h"
#include <fstream>
#include <cstring>

using namespace Enums;

int main() {

  std::ifstream inFS;

  std::string fileName;
  fileName = "circuit0.txt";
  inFS.open(fileName);
  char* s;

  
  inFS.getline(s, 256);

  char* temp1;
  std::vector<char*> temp2;
  temp1 = strtok(s, " ");
  temp2.push_back(temp1);

  while (temp1 != NULL) {
    temp1 = strtok(s, " ");
    temp2.push_back(temp1);
  }

  if (temp2[0] == "CIRCUIT") {
    char* name = temp2[1];

    while (!inFS.eof()) {

      inFS.getline(s, 256);

      char* temp1;
      std::vector<char*> temp2;
      temp1 = strtok(s, " ");
      temp2.push_back(temp1);

      while (temp1 != NULL) {
        temp1 = strtok(s, " ");
        temp2.push_back(temp1);
      }

      if (temp2[0] == "INPUT") {
        char* wireName = temp2[1];
        char* wireNum = temp2[2];
        //to do, create wire with above info
      }
      else if (temp2[0] == "OUTPUT") {
        char* wireName = temp2[1];
        char* wireNum = temp2[2];
        //to do, create wire with above info
      }
      else if (temp2[0] == "NOT") {
        char* delay = temp2[1];
        char* input1 = temp2[2];
        char* output = temp2[3];
        //to do, create gate containing above info
      }
      else {
        char* delay = temp2[1];
        char* input1 = temp2[2];
        char* input2 = temp2[3];
        char* output = temp2[4];
        //to do, create gate containing above info
      }

    }
  }
  else if (temp2[0] == "VECTOR") {
    while (!inFS.eof()) {

      inFS.getline(s, 256);

      char* temp1;
      std::vector<char*> temp2;
      temp1 = strtok(s, " ");
      temp2.push_back(temp1);

      while (temp1 != NULL) {
        temp1 = strtok(s, " ");
        temp2.push_back(temp1);
      }

    }
  }
    
  

  std::cout << "Hello World!" << std::endl;
  
  std::priority_queue<Event> queue;
  queue.push(*new Event(2, 3, WireValue::OFF, 0));
  queue.push(*new Event(1, 4, WireValue::OFF, 1));
  queue.push(*new Event(4, 16, WireValue::OFF, 2));
  queue.push(*new Event(2, 1, WireValue::OFF, 3));
  queue.push(*new Event(2, 3, WireValue::OFF, 4));
  queue.push(*new Event(2, 3, WireValue::OFF, 5));

  int size = queue.size();
  for (int i = 0; i < size; i++) {
    queue.top().print();
    queue.pop();
  }

  int a;
  std::cin >> a;
  
  return 0;
}