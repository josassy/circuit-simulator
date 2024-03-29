/*******************************************************************************
* File:       main.cpp
* Name:       Josiah Lansford, Benjamin Harless
* Date:       4 December 2019
* Assignment: HW6 - Circuit Simulator
* Purpose:    
*******************************************************************************/
#include <iostream>
#include <queue>
#include "Event.h"
#include "Enums.h"
#include "Circuit.h"
#include "Gate.h"
#include <fstream>
#include <sstream>
#include <cstring>

using namespace Enums;

/**
 * Convert space-delimited string into vector<string>
 * @param {string} line: A space-delimited string to split
 */
std::vector<std::string> stringToVector(std::string line) {
  // Convert string into stringstream
  std::istringstream ss(line);

  // Extract into vector<string>
  std::string token;
  std::vector<std::string> result;
  while (!ss.eof()) {
    token = "";
    ss >> token;
    if (token != "") {
      result.push_back(token);
    }
  }

  return result;
}

void usage() {
  std::cout << "Options:\n-h\tShow usage statement\n-v\tPrint verbose output" 
    << std::endl;
}

int runSimulation(std::string circuitFile, std::string vectorFile, 
  bool verbose) {
  std::ifstream inFS;

  // Parse circuit file
  inFS.open(circuitFile);
  std::string line;

  if (!inFS.is_open()) {
    std::cout << "Unable to open file " << circuitFile << '.' << std::endl;
    return 1;
  }

  // Get first line of file to string
  std::getline(inFS, line);

  // Convert string line into delimited vector
  std::vector<std::string> stringVector = stringToVector(line);

  // If the file starts with CIRCUIT, we have the correct file
  if (stringVector.at(0) != "CIRCUIT") {
    std::cout << "File " << circuitFile << " is not a valid CIRCUIT file." 
      << std::endl;
    return 1;
  }

  std::cout << "Simulating " << circuitFile << "." << std::endl;

  // Declare circuit object
  Circuit circuit;

  // Initialize circuit with name on first line
  circuit = Circuit(stringVector.at(1));

  // Iterate through rest of circuit file, adding wires as appropriate
  while (!inFS.eof()) {

    // Get next line from file
    std::getline(inFS, line);

    // If the line is empty, stop
    if (line.length() == 0) {
      break;
    }

    // Separate line into vector
    stringVector = stringToVector(line);

    // If any exceptions are thrown, skip the line
    try {
      // Handle wire creation
      if (stringVector.at(0) == "INPUT" || stringVector.at(0) == "OUTPUT") {

        // If there are less than two arguments, invalid wire definition
        if (stringVector.size() < 3) {
          throw std::exception();
        }

        std::string wireName = stringVector.at(1);
        int wireNum = std::stoi(stringVector.at(2));

        // Create wire & set its name as defined
        circuit.getWire(wireNum)->setName(wireName);
      }

      // Handle gates
      // Special case: NOT gate only has 1 input
      else if (stringVector.at(0) == "NOT") {

        // If there are less than 4 arguments, invalid gate definition
        if (stringVector.size() < 4) {
          throw std::exception();
        }

        GateType gateType = strToGateType(stringVector.at(0));
        int delay = std::stoi(stringVector.at(1));
        int input1 = std::stoi(stringVector.at(2));
        int output = std::stoi(stringVector.at(3));

      Gate* gate = new Gate(gateType, delay, circuit.getWire(input1), nullptr, 
        circuit.getWire(output));

        circuit.getWire(input1)->setGate(gate);
      }
      else {

        // If there are less than 5 arguments, invalid gate definition
        if (stringVector.size() < 5) {
          throw std::exception();
        }

        GateType gateType = strToGateType(stringVector.at(0));
        int delay = std::stoi(stringVector.at(1));
        int input1 = std::stoi(stringVector.at(2));
        int input2 = std::stoi(stringVector.at(3));
        int output = std::stoi(stringVector.at(4));

        Gate* gate = new Gate(gateType, delay, circuit.getWire(input1), 
          circuit.getWire(input2), circuit.getWire(output));
        circuit.getWire(input1)->setGate(gate);
        circuit.getWire(input2)->setGate(gate);
      }
    }
    // Catch all exceptions caused by bad input file, and ignore them, skipping line
    catch (...) {
      std::cout << "Warning: Invalid wire or gate definition " << line << std::endl;
    }
  }

  // At this point, circuit structure should be complete
  inFS.close();

  if (verbose) {
    // Print finished circuit structure:
    circuit.printSummary();
  }

  // Parse vector file
  inFS.open(vectorFile);

  if (!inFS.is_open()) {
    std::cout << "Unable to open file " << vectorFile << '.' << std::endl;
    return 1;
  }

  // Get first line of file to string
  std::getline(inFS, line);

  // Convert string line into delimited vector
  stringVector = stringToVector(line);

  // If file starts with VECTOR, we have the right vector file
  if (stringVector.at(0) != "VECTOR") {
    std::cout << "File " << vectorFile << " is not a valid VECTOR file." 
      << std::endl;
    return 1;
  }

  // Iterate through rest of VECTOR file, scheduling events as appropriate
  while (!inFS.eof()) {

    // Get next line from file
    std::getline(inFS, line);

    // If the line is empty, stop and skip line
    if (line.length() == 0) {
      break;
    }

    // Separate line into vector
    stringVector = stringToVector(line);

    // Gather event details from vector
    // If there are any exceptions thrown skip line
    try {
      // If there are less than 4 arguments, invalid vector definition
      if (stringVector.size() < 4) {
        throw std::exception();
      }

      Wire* wire = circuit.getWire(stringVector.at(1));
      int time = std::stoi(stringVector.at(2));
      WireValue val = charToWireVal(stringVector.at(3)[0]);


      // Add event to event queue
      // Even though scheduleEvent takes a delay
      // we know that at this point currTime=0
      circuit.scheduleEvent(wire, val, time);
    }
    catch (...) {
      std::cout << "Warning: Invalid vector definition " << line << std::endl;
    }
  }

  // At this point, all events should be in the event queue.
  circuit.processEvents(verbose);
  circuit.printHistory();

  return 0;

}

int main(int argc, char** argv) {

  bool verbose = false;
  // If args provided, parse them
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      // User passed option
      if (argv[i][0] == '-') {
        // Print usage statement
        if (std::strchr(argv[i], 'h') != nullptr) {
          usage();
        }
        // Enable verbose output
        if (std::strchr(argv[i], 'v') != nullptr) {
          verbose = true;
        }
      }
    }
  }

  bool done = false;
  while (!done) {
    std::cout << "Enter the name of the circuit test file (base name only):  ";
    std::string baseName;
    std::cin >> baseName;

    std::string circuitFile = baseName + ".txt";
    std::string vectorFile = baseName + "_v.txt";

    int result = runSimulation(circuitFile, vectorFile, verbose);
    // function returned with error. Attempt to correct circuit name.
    if (result == 1) {
      std::cout << "Let's try again." << std::endl;
    }
    // circuit was processed normally
    else {
      // Loop until valid input
      while (true) {
        std::cout << "Would you like to simulate another circuit? (y/n):  ";
        std::string response;
        std::cin >> response;
        if (response.length() > 0) {
          char letter = tolower(response[0]);
          if (letter == 'n') {
            done = true;
            break;
          }
          if (letter == 'y') {
            break;
          }
        }
        // user didn't say yes or no
        std::cout << "Invalid input" << std::endl;
      }
    }
  }
}
