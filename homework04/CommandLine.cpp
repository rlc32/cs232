/* CommandLine.cpp defines the methods for CommandLine, a class to read a command-line.
 * Student Names: Russell Clousing Alastair Van Maren
 * Written by Russell Clousing
 * Date: February 24, 2018.
 */
#include "CommandLine.h"
#include <istream>
//defualt constructor for CommandLine
CommandLine::CommandLine(){
    argc = 0;
}
//explicit constructor for CommandLine
CommandLine::CommandLine(istream& in){
    argc = 0;
    noAmpersand_var = true;
    string argString;
    getline(in, argString);
    istringstream splitArgString (argString);
    string temp;
    while(splitArgString >> temp){
        if (strcmp(temp.c_str(), "&") == 0){
            noAmpersand_var = false;
        } else {
            myArgv.push_back(temp);
            argc++;
        }
    }
    argv = new char*[myArgv.size()];

    for (int i; i < myArgv.size(); i++){
        argv[i] = new char[myArgv[i].size()];
        strcpy(argv[i], myArgv[i].c_str());
    }
}
char* CommandLine::getCommand() const {
    return argv[0];
}
int CommandLine::getArgCount() const {
    return argc;
}
char** CommandLine::getArgVector() const {
    return argv;
}

char* CommandLine::getArgVector(int i) const{
	return argv[i];
}

bool CommandLine::noAmpersand() const {
    return noAmpersand_var;
}

CommandLine::~CommandLine(){
    for (size_t i = 0; i < myArgv.size(); i++){
        delete[] argv[i];
    }
    delete[] argv;
}
