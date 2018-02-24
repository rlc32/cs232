/* CommandLine.h defines the methods for CommandLine, a class to read a command-line.
 * Student Names: Russell Clousing, Alastair Van Maren
 * Date: February 24, 2018.
 */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
using namespace std;

class CommandLine {
public:
    CommandLine();
    CommandLine(istream& in) ;
    char* getCommand() const ;
    int getArgCount() const ;
    char** getArgVector() const ;
    char* getArgVector(int i) const ;
    bool noAmpersand() const ;
    virtual ~CommandLine() ;
private:
    int argc;
    char** argv;
    vector<string> myArgv;
    bool noAmpersand_var;
};
