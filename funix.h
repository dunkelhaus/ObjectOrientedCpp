
#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"

const int COMMAND_LENGTH = 80;
const int NUM_COMMANDS = 5;
const int MAX_ARGUMENTS = 40;

typedef struct
{
  Directory* currentDirectory;
  int umask;
  int time;
} Funix;

void cd(Funix *funix, int argCount, const char *arguments[]);
  // calls cd() with currentDirectory as one of its parameters
int eXit(Funix *funix, int argCount, const char *arguments[]);
  // checks "exit" command, returns 0 on proper exit
void getCommand(Funix *funix, char *command);  
  // writes prompt and reads command
void init(Funix *funix);  
  // creates currentDirectory, and sets umask and time
void ls(Funix *funix, int argCount, const char *arguments[]);
  // calls ls() with currentDirectory as one of its parameters
void mkdir(Funix *funix, int argCount, const char *arguments[]);
  // calls mkdir() with currentDirectory as one of its parameters
int processCommand(Funix *funix, char *command);  // returns 0 on proper exit
void run(Funix *funix);  
  // reads and processes commands in a loop until proper exit
void umask(Funix *funix, int argCount, const char *arguments[]);
  // checks "umask" command and executes it if it is proper
void writePrompt(Funix *funix);  // shows path and '#'
#endif

