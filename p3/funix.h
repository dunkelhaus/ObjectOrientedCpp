// Author: Sean Davis
#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"

const int COMMAND_LENGTH = 80;
const int NUM_COMMANDS = 5;
const int MAX_ARGUMENTS = 40;

class Funix
{
  Directory *currentDirectory;
  int umask;
  int time;
  void cd(int argCount, const char *arguments[]);
    // calls cd() with currentDirectory as one of its parameters
  int eXit(int argCount, const char *arguments[])const;
    // checks "exit" command, returns 0 on proper exit
  void getCommand(char *command);  
    // writes prompt and reads command
  void ls(int argCount, const char *arguments[])const;
    // calls ls() with currentDirectory as one of its parameters
  void mkdir(int argCount, const char *arguments[]);
    // calls mkdir() with currentDirectory as one of its parameters
  int processCommand(char *command);  // returns 0 on proper exit
  void setUmask(int argCount, const char *arguments[]);
    // checks "umask" command and executes it if it is proper
  void writePrompt()const;  // shows path and '#'
public:
  Funix();  
    // creates currentDirectory, and sets umask and time
  ~Funix();
  void run();  
    // reads and processes commands in a loop until proper exit
}; //class Funix
#endif

