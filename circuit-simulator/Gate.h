/*******************************************************************************
* File:       Gate.h
* Name:       Josiah Lansford, Benjamin Harless
* Date:       4 December 2019
* Assignment: HW6 - Circuit Simulator
* Purpose:    Represents a logic gate with a type and Wire inputs and output.
*******************************************************************************/
#pragma once
#include "Enums.h"
using namespace Enums;

class Wire;

class Gate {
public:
  Gate(GateType t, int d, Wire* i1, Wire* i2, Wire* o);
  Wire* getOut() const { return out; }
  int getDelay() const { return delay; }
 
  /**
  * Process what the output of the gate should be given its current inputs
  * @return {WireValue} The value of the gate, used in scheduleEvent()
  */
  WireValue eval();

 /**
  * Process gate output if one of its inputs was changed to provided state
  * Used for calculating future gate output without actually making change
  * @param  {WireValue} state that the input is about to have
  * @param  {Wire*}     input the input that is about to change state
  * @return {WireValue} The value of the gate should the changes be made
  */
  WireValue eval(WireValue state, Wire* input);
  GateType getType() const { return type; }

private:
  WireValue doLogic(WireValue s1, WireValue s2);
  Wire* in1;
  Wire* in2;
  Wire* out;
  GateType type;
  int delay;
};