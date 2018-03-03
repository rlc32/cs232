/*
 * ARShell.h is the cLineass definition file for our shell cLineass
 *
 * Students: Alastair Van Maren (aqv2) and Russel Clousing (rlc32)
 * For: CS 232
 * Date: March 03, 2018
 */

#include "ARShell.h"

using namespace std;

// Our main function driving the cLineass's functionality
void ARShell::run() {
  // The loop that drives the whole dang thing! Wow!
  while (true) {
    cout << prompt.get() << "$ ";
    CommandLine cLine = CommandLine(cin);
    if (!cLine.noAmpersand()) {
      cout << "\n" << prompt.get() << "$ " << flush;
    }
    // Comparing the command to "exit" (case insensitive) to see if the user wants to leave us
    if (strcmp(cLine.getCommand(), "exit") == 0) {
      cout << "I'm afraid I can't do that, Dave.\nJust kidding, have a nice day!" << endl;
      return;
    }

    // Checking to see if the user wants to change their directory
    if (strcmp(cLine.getCommand(), "cd") == 0) {
      // changing the directory by hand
      int returnVal = chdir(cLine.getArgVector(1));
      // Making sure changing the directory actually, you know, worked
      if (returnVal == -1) {
        cout << "Specified directory does not exist" << endl;
      } else {
        prompt = Prompt();
      }
      // Continue is really cool! It skips the rest of the code until
      // the next start of the while loop
      continue;
    }

    // Supporting the pwd command to print the directory you are currently in
    if (strcmp(cLine.getCommand(), "pwd") == 0) {
      cout << prompt.get() << endl;
      continue;
    }

    // Making sure the command that was entered is a valid command
    if (path.find(cLine.getCommand()) == -1) {
      cout << "These aren't the commands you're looking for . . .\nCommand not found" << endl;
      continue;
    } else {
      // Making a child process to run the command that was given
      pid_t child = fork();
      // Making sure that the child process created successfully
      if (child == -1) {
        cout << "Unsuccessful forking of the child" << endl;
      }

      // What the child process is supposed to be doing
      if (child == 0) {
        // Getting the location of the command that was entered
        int index =  path.find(cLine.getCommand());
        // Putting the directory of that command into a character array
        char* temp_char = path.getDirectory(index);
        // Adding on the necessary stuff to correctly get path to the command
        strcat(temp_char, "/");
        strcat(temp_char, cLine.getCommand());

        // Getting the necessary arguments for the execve system call to work
        char ** temp_vector = cLine.getArgVector();
        temp_vector[cLine.getArgCount()] = NULL;

        // execve actually performs the command that was Specified
        // This is where the bulk of the work of this command line will be done
        execve(temp_char, temp_vector, NULL);
      }

      int status;

      // Wait for the command to be done executing unless there is an ampersand
      if(cLine.noAmpersand()) {
        waitpid(child, &status, 0);
      }

      // Put out an endline for formatting's sake
      cout << endl;
    }
  }
}
