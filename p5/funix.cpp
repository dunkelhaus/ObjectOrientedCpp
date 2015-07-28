#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "funix.h"
#include "directory.h"
#include "permissions.h"

using namespace std;

Funix::Funix()
// creates currentDirectory, and sets umask and time
{
  currentDirectory = new Directory("/", NULL); 
  ifstream inf("directories.txt");
  
  if (inf)
  {
    inf >> *this;
    inf.close();
  }  // if directories.txt exists
}  // Funix()


Funix::~Funix()
{
  const char *arguments[2] = {"cd", ".."};
  Directory *next = currentDirectory->cd(2, arguments);
  
  while(currentDirectory != next)
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments);
  }  // while currentDirectory not root
  
  delete currentDirectory;
}  // ~Funix())

  
int Funix::eXit(int argCount, const char *arguments[])
{
  // checks "exit" command, returns 0 on proper exit
  
  if (argCount > 1)
  {
    cout << "usage: exit\n";
    return 1;
  }  // if more than one argument
  
  const char *arguments2[2] = {"cd", ".."};
  Directory *next = currentDirectory->cd(2, arguments2);
  
  while(currentDirectory != next)
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments2);
  }  // while currentDirectory not root
  
  ofstream outf("directories.txt");
  outf << *this;
  outf.close();
  return 0;
}  // eXit()

void Funix::getCommand(char *command)  // writes prompt and reads command
{
  writePrompt();
  cin.getline(command, COMMAND_LENGTH);
}  // getCommand()


int Funix::processCommand(char *command)  // returns 0 on proper exit
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask", 
    "chmod", "cp"};
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
      case 0: currentDirectory = currentDirectory->cd(argCount, arguments); 
              break;
      case 1: return eXit(argCount, arguments);
      case 2: currentDirectory->ls(argCount, arguments); break;
      case 3: currentDirectory->mkdir(argCount, arguments); break;
      case 4: currentDirectory -> permissions.setUmask(argCount, arguments);
                break;
      case 5: currentDirectory->permissions.chmod(argCount, 
              arguments, currentDirectory); 
                break; 
      case 6: currentDirectory->cp(argCount, arguments); break;
      default: cout << arguments[0] << ": Command not found.\n";
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

void Funix::writePrompt() const  // shows path and '#'
{
  currentDirectory->showPath();
  cout << " # ";
}  // writePrompt()


ostream& operator<< (ostream &os, const Funix &rhs)
{
  rhs.currentDirectory -> permissions.umaskOut(os);
  os << endl;
  os << *rhs.currentDirectory;
  return os;
}  // operator<<
 

istream& operator>> (istream &is, Funix &rhs)
{
  rhs.currentDirectory -> permissions.umaskIn(is);
  is.ignore(10, '\n');
  is >> *rhs.currentDirectory;
  return is;
}  // operator>>