#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"
#include <iostream>
#include <fstream>

using namespace std;

const int COMMAND_LENGTH = 80;
const int NUM_COMMANDS = 6;
const int MAX_ARGUMENTS = 40;

class Funix
{
  Directory *currentDirectory;
  int umask;
  
  int eXit(int argCount, const char *arguments[]);
    // checks "exit" command, returns 0 on proper exit
  void getCommand(char *command);  
    // writes prompt and reads command
  int octalConverter(int decimal);
    // converts to octal
  int processCommand(char *command);  
    // returns 0 on proper exit
  void setUmask(int argCount, const char *arguments[]);
    // checks "umask" command and executes it if it is proper
  void writePrompt() const;  // shows path and '#'
public:
  friend std::ostream& operator<<(std::ostream& os, const Funix& funi);
  friend std::istream& operator>>(std::istream& is, const Funix& funi);
  Funix(); 
  ~Funix();
  void run();  
  int decimalConverter(int n);
    // converts octal to decimal
    // reads and processes commands in a loop until proper exit
    // creates currentDirectory, and sets umask and you-know-what
 
};  // class Funix
#endif

