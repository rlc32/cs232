/* Prompt.h is the header file for our prompt class
* Written by: Alastair Van Maren (aqv2) in consult with partner: Russell Clousing (rlc32)
* Date: February 24th, 2018
* For: CS 232, Professor Norman
*/

#ifndef PROMPT_H_
#define PROMPT_H_

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <unistd.h>

// Our namespace declaration
using namespace std;

// Our class declaration
class Prompt {
// Public-facing methods
public:
  Prompt();
  char* get() const;
// Private-facing instance variables
private:
  char buff[PATH_MAX + 1];
  char* current_folder;
};

#endif
