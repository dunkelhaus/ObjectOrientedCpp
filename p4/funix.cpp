#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "funix.h"
#include "directory.h"
#include "Time.h"

using namespace std;

ofstream out;
ifstream in;

Funix::Funix() : umask(022)
// creates currentDirectory, and sets umask and time
{
  currentDirectory = new Directory("/", umask, NULL); 
  out.open("directories.txt"); 
  in >> *this;
}  // Funix()


Funix::~Funix()
{
  const char *arguments[2] = {"cd", ".."};
  Directory *next = currentDirectory->cd(2, arguments);
  
  while(currentDirectory != next)// while
  {
    currentDirectory = next;
    next = currentDirectory->cd(2, arguments);
  }  // while currentDirectory not root
  
  delete currentDirectory;
}  // ~Funix())

ostream& operator<<(std::ostream& os, const Funix& funi)
{
  return os << funi.umask << "\n" << *funi.currentDirectory;
}// ostreamop

istream& operator>>(std::istream& is, const Funix& funi)
{
    char* um = new char [80];
    sprintf(um, "%d", funi.umask);
    
    is >> um >> *funi.currentDirectory;
    return is;   
}// intreamop

int Funix::eXit(int argCount, const char *arguments[])
{
  // checks "exit" command, returns 0 on proper exit
  
  if (argCount > 1)// if
  {
    cout << "usage: exit\n";
    return 1;
  }  // if more than one argument
  
  out << *this;
  out.close();
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
                                   "chmod"};
  const char *arguments[MAX_ARGUMENTS];
  char *ptr;
  int argCount = 0, commandNum;
  ptr = strtok(command, " ");
  
  while (ptr)
  {
    arguments[argCount++] = ptr;
    ptr = strtok(NULL, " ");
  }  // while more arguments in the command line
  
  if (argCount > 0)// if
  {
      
    for (commandNum = 0; commandNum < NUM_COMMANDS; commandNum++)
    {
        
      if (strcmp(arguments[0], commands[commandNum]) == 0)// if
        break;
      
    }  // for each possible command

    switch (commandNum)
    {
      case 0: currentDirectory = currentDirectory->cd(argCount, arguments); 
        break;
      case 1: return eXit(argCount, arguments);
      case 2: currentDirectory->ls(argCount, arguments); break;
      case 3: currentDirectory->mkdir(argCount, arguments, umask); 
        break;
      case 4: setUmask(argCount, arguments); break;
      case 5: currentDirectory -> chmod(argCount, arguments, umask); break;
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


void Funix::setUmask(int argCount, const char *arguments[])
  // checks "umask"
{
  if (argCount > 2)
  {
    cout << "umask: Too many arguments.\n" ;
    return;
  }  // arg
  
  else // argCount not greater than 2
    if (argCount == 1)
  {
      cout << oct << umask << endl;
      return;
  } // prints umask 
  
    else // argCount not 1
      if (arguments[1][0] < '0' || arguments[1][0] > '7' || 
          arguments[1][1] > '7' || arguments[1][2] > '7' || 
          strlen(arguments[1]) > 3 || (isalpha (arguments[1][1]) != 0) || 
          (isalpha (arguments[1][2]) != 0))
      {
        cout << "umask: Improper mask.\n";
        return;
      }  //if wrong
  
  umask = strtol(arguments[1], NULL, 8);
}  // umask

int Funix::decimalConverter(int octal) // Function to convert octal to decimal
{
    int decimal = 0, i = 0, remainder;
    
    while (octal != 0)
    {
        remainder = octal % 10;
        octal /= 10;
        decimal += remainder * pow(8, i);
        ++i; 
        
    }// while
    
    return decimal;
}// converter

void Funix::writePrompt() const  // shows path and '#'
{
  currentDirectory->showPath();
  cout << " # ";
}  // writePrompt()

