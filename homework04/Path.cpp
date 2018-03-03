/* Path.cpp is the class definition file for our Path class
 * It creats an array of folders based on the PATH
 * Written by: Alastair Van Maren (aqv2) in consult with partner: Russell Clousing (rlc32)
 * Date: February 24th, 2018
 * For: CS 232, Professor Norman
 */

#include "Path.h"

/* Our contstructor for a Path. It builds an array of folders to look inside of.
 */
Path::Path() {
  /* char+ is an array of characters, which is different from string,
   * and easier to iterate through
   */
  char* envPath;
  envPath = getenv ("PATH");

  char* splitter;
  /* strtok goes through the specified string and breaks returns a chunk of
   * it delimited by the second parameter
   */
  splitter = strtok(envPath, ":");
  while(splitter != NULL) {
    // push_back adds an item to the end of the vector
    folders.push_back(splitter);

    /* strtok uses NULL here because in subsequent calls to
     * strtok it treats NULL as meaning the same string earlier
     */
    splitter = strtok(NULL, ":");
  }
}

/* find() finds a program stored in a one of the specified folders
 */
int Path::find(const string& program) const {
  int index = -1;
  /* dirent.h allows us to iterate through a list of folders and find
   * something inside of them (which is the exact goal of this function)
   */
  DIR *folder;
  struct dirent *ent;
  for(unsigned i = 0; i < folders.size(); i++) {
    if((folder = opendir(folders[i]))!= NULL) {
      while((ent = readdir(folder)) != NULL) {
        if(ent->d_name == program) {
          index = i;
        }
      }
      closedir(folder);
    }
  }
  return index;
}
/* getDirectory() allows us to get a specific folder based on its index
 * in the vector of folders created by our constructor
 * TODO: make sure we don't allow indices larger than our vector
 */
char* Path::getDirectory(int i) const {
  if(i > folders.size()) {
    throw range_error("Index too large");
  }
  char* temp_folder = folders[i];
  return temp_folder;
}
