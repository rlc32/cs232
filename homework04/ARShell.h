/*
 * ARShell.h header file for our shell simulation class
 *
 * Students: Alastair Van Maren (aqv2) and Russel Clousing (rlc32)
 * For: CS 232
 * Date: March 03, 2018
 */

#ifndef ARSHELL_H_
#define ARSHELL_H_

#include <iostream>
#include "Prompt.h"
#include "CommandLine.h"
#include "Path.h"

#include <sys/wait.h>

using namespace std;

// The class definition
class ARShell {

public:
  // Declaration of public methods
  ARShell() {};
  void run();

private:
  // Declaration of private instance variables
  Prompt prompt;
  Path path;
};

#endif
