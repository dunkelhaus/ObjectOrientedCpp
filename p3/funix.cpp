// Author: Sean Davis
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "funix.h"
#include "directory.h"
using namespace std;

Funix::Funix() : umask(0), time(0) // creates currentDirectory
{
  currentDirectory = new Directory("/", umask, time, NULL);
}  // init()

Funix::~Funix()
{
  const char *arguments[20];
  arguments[0] = "cd";
  arguments[1] = "..";
  
  while(currentDirectory->cd(2, arguments) != currentDirectory)
  {
    currentDirectory = currentDirectory->cd(2, arguments);
  } // while()
  
  delete currentDirectory;
}// destroys objects

void Funix::cd(int argCount, const char *arguments[])
// calls cd() with currentDirectory as one of its parameters
{
  currentDirectory = 
    currentDirectory -> cd(argCount, arguments); 
}  // cd())


int Funix::eXit(int argCount, const char *arguments[])const
{
  // checks "exit" command, returns 0 on proper exit
  
  if (argCount > 1)
  {
    cout << "usage: exit" << "\n"; 
    return 1;
  }  // if more than one argument
  
  return 0;
}  // eXit()

void Funix::getCommand(char *command)  // writes prompt and reads command
{
  writePrompt();
  cin.getline(command, COMMAND_LENGTH);
  time++;
}  // getCommand()

void Funix::ls(int argCount, const char *arguments[])const
  // calls ls() with currentDirectory as one of its parameters
{
  currentDirectory -> ls(argCount, arguments);
}  // ls()


void Funix::mkdir(int argCount, const char *arguments[])
  // calls mkdir() with currentDirectory as one of its parameters
{
  currentDirectory -> mkdir(argCount, arguments, umask, 
    time);
}  // mkdir()


int Funix::processCommand(char *command)  // returns 0 on proper exit
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask"};
  const char *arguments[MAX_ARGUMENTS];
  char *ptr;
  int argCount = 0, commandNum;
  ptr = strtok(command, " ");
  
  while (ptr)
  {
    arguments[argCount++] = ptr;
    ptr = strtok(NULL, " ");
  }  // while more arguments in the command line
  
  if (argCount > 0)
  {
    for (commandNum = 0; commandNum < NUM_COMMANDS; commandNum++)
    {
      if (strcmp(arguments[0], commands[commandNum]) == 0)
        break;
    }  // for each possible command

    switch (commandNum)
    {
      case 0: cd(argCount, arguments); break;
      case 1: return eXit(argCount, arguments);
      case 2: ls(argCount, arguments); break;
      case 3: mkdir(argCount, arguments); break;
      case 4: setUmask(argCount, arguments); break;
      default: cout << arguments[0] << ":" << " Command not found." << "\n"; 
    }  // switch on commandNum   
  }  // if at least one argument
  
  return 1;
}  // processCommand()


void Funix::run() 
// reads and processes commands until proper exit
{
  char command[COMMAND_LENGTH];
  getCommand(command);
  
  while (processCommand(command))
    getCommand(command);
}  // run()


void Funix::setUmask(int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{
  if (argCount != 2)
  {
    cout << "usage: umask octal" << "\n";
    return;
  }  // if wrong number of arguments
  
  if (arguments[1][0] < '0' || arguments[1][0] > '7' 
      || strlen(arguments[1]) > 1)
  {
    cout << "umask: octal must be between 0 and 7" << "\n"; 
    return;
  }  // if incorrect octal
  
  umask = atoi(arguments[1]);
}  // umask()



void Funix::writePrompt()const  // shows path and '#'
{
  currentDirectory -> showPath();
  cout << " # ";
}  // writePrompt()

