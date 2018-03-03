/* Prompt.cpp is the implementation file for our Prompt class
* Written by: Alastair Van Maren (aqv2) in consult with partner: Russell Clousing (rlc32)
* Date: February 24th, 2018
* For: CS 232, Professor Norman
*/

#include "Prompt.h"

// Namespace declaration
using namespace std;

/* Our consructor. Gets the current working directory using the getcwd call
 */
Prompt::Prompt() {
  current_folder = getcwd(buff, PATH_MAX + 1);
  // strcat concatenates the two specified strings
  strcat(current_folder, "/ARShell");
}

/* get() allows us to access the current_folder variable
 */

 char* Prompt::get() const {
   return current_folder;
 }
