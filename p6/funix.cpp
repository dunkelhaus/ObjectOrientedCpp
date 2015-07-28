// Author: Sean Davis
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "permissions.h"
#include "funix.h"
#include "directory.h"

using namespace std;

Funix::Funix() 
// creates currentDirectory, and sets umask and time
{
  currentDirectory = new Directory("/", NULL, "root"); 
  ifstream inf("directories.txt");
  strcpy(user, "root");
  
  if (inf)
  {
    inf >> *this;
    inf.close();
  }  // if directories.txt exists
}  // Funix()


Funix::~Funix()
{
  const char *arguments[2] = {"cd", ".."};
  strcpy(user, "root");
  Directory *next = currentDirectory->cd(2, arguments, user);
 
  
  while(currentDirectory != next)
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments, user);
  }  // while currentDirectory not root
  
  delete currentDirectory;
}  // ~Funix()

  
void Funix::chown(int argCount, const char *arguments[])
{
  if (strcmp(user, "root") != 0)
  {
    cout << "chown: Permission denied\n";
    return;
  }  // if not root
  
  if (argCount >= 2 && strlen(arguments[1]) > 8)
  {
    cout << "chown: user " << arguments[1] << " does not exist\n";
    return;
  }  // if owner too long
  
  currentDirectory->chown(argCount, arguments);
  
}  // chown()


int Funix::eXit(int argCount, const char *arguments[])
{
  // checks "exit" command, returns 0 on proper exit
  
  if (argCount > 1)
  {
    cout << "usage: exit\n";
    return 1;
  }  // if more than one argument
  
  strcpy(user, "root");
  const char *arguments2[2] = {"cd", ".."};
  Directory *next = currentDirectory->cd(2, arguments2, user);
  
  while(currentDirectory != next)
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments2, user);
  }  // while currentDirectory not root
  
  ofstream outf("directories.txt");
  outf << *this;
  outf.close();
  return 0;
}  // eXit()

void Funix::getCommand(char *command) const // writes prompt and reads command
{
  writePrompt();
  cin.getline(command, COMMAND_LENGTH);
}  // getCommand()


int Funix::processCommand(char *command)  // returns 0 on proper exit
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask", 
    "chmod", "cp", "su", "chown", "touch"};
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
      case 0: 
        currentDirectory = currentDirectory->cd(argCount, arguments, user); 
        break;
      case 1: return eXit(argCount, arguments);
      case 2: currentDirectory->ls(argCount, arguments, user); break;
      case 3: currentDirectory->mkdir(argCount, arguments, user); break;
      case 4: Permissions::setUmask(argCount, arguments); break;
      case 5: currentDirectory->chmod(argCount, arguments, user); break; 
      case 6: currentDirectory->cp(argCount, arguments, user); break;
      case 7: su(argCount, arguments); break;
      case 8: chown(argCount, arguments); break;
      case 9: currentDirectory->touch(argCount, arguments, user); break;
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


void Funix::su(int argCount, const char *arguments[])
{
  if (argCount != 2)
  {
    cout << "usage: su user_name\n";
    return;
  }  // if only "su"
  
  if (strlen(arguments[1]) > 8)
  {
    cout << "su: user " << arguments[1] << " does not exist\n";
    return;
  }  // if user too long
  
  strcpy(user, arguments[1]);
}  // su())


void Funix::writePrompt() const  // shows path and '#'
{
  currentDirectory->showPath();
  cout << " # ";
}  // writePrompt()


ostream& operator<< (ostream &os, const Funix &rhs)
{
  Permissions::writeUmask(os);
  rhs.currentDirectory->write(os, 0);
  return os;
}  // operator<<
 

istream& operator>> (istream &is, Funix &rhs)
{
  Permissions::readUmask(is);

  is >> *rhs.currentDirectory;
  return is;
}  // operator>>
