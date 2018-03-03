/* Path.h is the header file for our path class
* Written by: Alastair Van Maren (aqv2) in consult with partner: Russell Clousing (rlc32)
* Date: February 24th, 2018
* For: CS 232, Professor Norman
*/

#ifndef PATH_H_
#define PATH_H_

#include <stdlib.h>
#include <string>
#include <string.h> // for strtok, mostly
#include <vector> // for our vector of folders
#include <stdexcept>
#include <dirent.h> // for the various folder interaction functions seen in find()

using namespace std ;

// Our class declaration
class Path {
  // Methods accessible to the outside
public:
  Path();
  int find(const string& program) const;
  char* getDirectory(int i) const;

// Instance variables not accessible to the outside
private:
  char* envPath;
  vector<char*> folders;
};

#endif
