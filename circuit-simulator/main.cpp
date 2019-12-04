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
    ss >> token;
    result.push_back(token);
  }

  return result;
}

int main() {

  std::ifstream inFS;

  // TODO: Prompt for input files
  std::string circuitFile, vectorFile;
  circuitFile = "../vector files/circuit0.txt";
  vectorFile = "../vector files/circuit0_v.txt";

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

  // Declare circuit object
  Circuit circuit;

  // If the file starts with CIRCUIT, we have the correct file
  if (stringVector.at(0) == "CIRCUIT") {
    
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
      std::cout << line << std::endl;

      // Handle wire creation
      if (stringVector[0] == "INPUT" || stringVector[0] == "OUTPUT") {
        std::string wireName = stringVector[1];
        int wireNum = std::stoi(stringVector[2]);
        
        // Create wire & set its name as defined
        circuit.getWire(wireNum)->setName(wireName);
      }

      // Handle gates
      // Special case: NOT gate only has 1 input
      else if (stringVector[0] == "NOT") {
        GateType gateType = strToGateType(stringVector[0]);
        int delay = std::stoi(stringVector[1]);
        int input1 = std::stoi(stringVector[2]);
        int output = std::stoi(stringVector[3]);

        Gate* gate = new Gate(gateType, delay, circuit.getWire(input1), nullptr, circuit.getWire(output));

        circuit.getWire(input1)->setGate(gate);
      }
      else {
        GateType gateType = strToGateType(stringVector[0]);
        int delay = std::stoi(stringVector[1]);
        int input1 = std::stoi(stringVector[2]);
        int input2 = std::stoi(stringVector[3]);
        int output = std::stoi(stringVector[4]);

        Gate* gate = new Gate(gateType, delay, circuit.getWire(input1), circuit.getWire(input2), circuit.getWire(output));
         circuit.getWire(input1)->setGate(gate);
         circuit.getWire(input2)->setGate(gate);
      }
    }
  }
  else {
    // Invalid circuit file.
    std::cout << "File " << circuitFile << " is not a valid CIRCUIT file." << std::endl;
    return 1;
  }

  // At this point, circuit structure should be complete
  // Print circuit structure:
  inFS.close();
  circuit.printSummary();

  //// Parse vector file
  //inFS.open(vectorFile);

  //if (!inFS.is_open()) {
  //  std::cout << "Unable to open file " << vectorFile << '.' << std::endl;
  //  return 1;
  //}

  //// Get first line of file to string
  //std::getline(inFS, line);

  //// Convert string line into delimited vector
  //stringVector = stringToVector(line);


  //if (temp2[0] == "VECTOR") {
  //  while (!inFS.eof()) {

  //    inFS.getline(s, 256);

  //    char* temp1;
  //    std::vector<char*> temp2;
  //    temp1 = strtok(s, " ");
  //    temp2.push_back(temp1);

  //    while (temp1 != NULL) {
  //      temp1 = strtok(s, " ");
  //      temp2.push_back(temp1);
  //    }

  //  }
  //}
  //
  return 0;
}