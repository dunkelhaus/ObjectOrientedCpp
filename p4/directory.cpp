#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include "directory.h"
#include "Time.h"

using namespace std;

Directory::Directory(const char *nam, int umas, Directory *paren)
  : parent(paren), subDirectoryCount(0), umask(umas), subDirectories(NULL)
 {
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, umas);
  time.set();
 }  // Directory())

Directory::Directory(const char *nam)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
}// Directory

Directory::~Directory()
{
  delete [] name;
 
  for (int i = 0; i < subDirectoryCount; i++)
    delete subDirectories[i];

  delete [] subDirectories;
}  // ~Directory())

ostream& operator<<(ostream& outf, const Directory& directory)
{
  outf << directory.name << " " << directory.time << " " << 
          directory.permissions << " " << directory.subDirectoryCount << endl;
  
  for (int i = 0; i < directory.subDirectoryCount; i++)
    outf << directory.subDirectories[i]->name << " " << 
            directory.subDirectories[i]->time << " " << 
            directory.subDirectories[i]->permissions << " " << 
            directory.subDirectories[i]->subDirectoryCount << endl;
  
  return outf;
}// operator ostream

istream& operator>>(istream& isf, const Directory& directory)
{
    isf >> directory.name;
    isf >> directory.time;
    isf >> directory.permissions;
    char* count = new char [80];
    sprintf(count, "%d", directory.subDirectoryCount);
    // int n = itoa(directory.subDirectoryCount, count, 10);
    isf >> count;
    return isf;
    
    for (int i = 0; i < directory.subDirectoryCount; i++)
    {
        isf >> directory.subDirectories[i]->name;
        isf >> directory.subDirectories[i]->time;
        isf >> directory.subDirectories[i]->permissions;
        isf >> directory.subDirectories[i]->subDirectoryCount;
        return isf;
    }// for     
    
}// operatoristhis

bool Directory::operator==(const Directory& dir1) const
{
  while (name !=NULL && dir1.name != NULL)
  {
    if (strcmp(name, dir1.name) == 0)// compares
  return true;
    else // false
    return false;
  }// while
  
  return false;
}// ==
  
Directory* Directory::cd(int argCount, const char *arguments[])
{
    
  if (argCount != 2)// check count
  {
    cout << "usage: cd directoryName\n";
    return this;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)// cd ..
  {
    if (parent)// parent
      return parent;
    else  // this is root
      return this;
  }  // if cd ..

  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (Directory(arguments[1]) == *subDirectories[i])// if same
    {
      if (subDirectories[i] -> permissions.isPermitted(3))// permission
      {
        return subDirectories[i];
      }// if
      else // else
      {
          cout << arguments[1] << ": Permission denied." << "\n";
          return this;
      }// else
    }// for
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()


void Directory::ls(int argCount, const char *arguments[])
{
    
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))// if
    cout << "usage: ls [-l]\n";
  
  else  // correct number of arguments
  {
      
    if (!(permissions.isPermitted(1)))// permitted
    {
        cout << "ls: cannot open directory .: Permission denied\n";
        return;
    }// permitted
    
    if (argCount == 1)  // simple ls
    {
        
      for (int i = 0; i < subDirectoryCount; i++)
        cout << subDirectories[i]->name << " ";
      
      cout << "\n";
    }  // if simple ls
    
    else  // must be ls -l
    {
        looper(argCount, arguments);
    }  // else is ls -l
    
  }  // else correct arguments
  
}  // ls()

void Directory::looper(int argCount, const char *arguments[])
{
    
    for (int i = 0; i < subDirectoryCount; i++)// for
      {
        subDirectories[i]->permissions.print();
        cout << " ";
        subDirectories[i]->time.print();
        cout << ' ' << subDirectories[i]->name << endl;
      }  // for each subdirectory
    
}// looper

void Directory::mkdir(int argCount, const char *arguments[], int umas)
{
    
  if (argCount == 1)// one word
  {
    cout << "mkdir: missing operand\n";
    cout << "Try 'mkdir --help' for more information.\n";
    return;
  }  // if too many arguments
  
  if (argCount >= 2)// more than 2
  {
      
    mkdirhelper(argCount, arguments, umas);
      
  }  // check if arguments
} // mkdir()

void Directory::mkdirhelper(int argCount, const char* arguments[], int umas)
{
    int count = 0;
    
    for (int i = 1; i <= argCount - 1; i++)// for
    {
        
      for (int j = 0; j < subDirectoryCount; j++)
      {
          
        if (Directory(arguments[i]) == *subDirectories[j])// compare
        {
          cout << "mkdir: cannot create directory ‘" << arguments[i] 
               << "’: File exists\n";
          count++;
        }  // if subdirectory already exists.
        
      }  // for each subdirectory
      
      if (count > 0)// count
      {
          count = 0;
          continue;
      }// if
      
      if (!(permissions.isPermitted(2)))// permitted
      {
          cout << "mkdir: cannot create directory ‘" << arguments[i] 
               << "’: Permission denied\n";
          continue;
      }// if
      
      mkdirhelper2(arguments, umas, i);
      
    } // loop through arguments
}// helper

void Directory::mkdirhelper2(const char* arguments[], int umas, int i)
{
    Directory **subDirectoriesTemp = new Directory*[subDirectoryCount + 1];
        
      for (int k = 0; k < subDirectoryCount; k++)
        subDirectoriesTemp[k] = subDirectories[k];
      
      delete [] subDirectories;
      subDirectories = subDirectoriesTemp;
      subDirectories[subDirectoryCount] = new Directory(arguments[i], umas, 
        this);
      time.set();
      subDirectoryCount++;
}// mkdir

void Directory::chmod(int argCount, const char *arguments[], int umas)
{
  int permissionNum = 0;
  permissionNum = atoi(arguments[1]);
  chmodhelper(argCount, arguments);
  
  if (argCount >= 3)// if
  {
      
    if (arguments[1][0] < '0' || arguments [1][0] > '7' || 
        strlen(arguments[1]) > 3)// if
    {
        cout << "chmod: invalid mode: ‘" << arguments[1] << "’\n";
        cout << "Try 'chmod --help' for more information." << "\n";
        return;
    }// if
    
    if (permissionNum < 0 || permissionNum > 777)// if
    {
      cout << "chmod: invalid mode: ‘" << arguments[1] << "’\n";
      cout << "Try 'chmod --help' for more information." << "\n";
      return;
    }  // if incorrect octal
        
    chmodhelper2(argCount, arguments, 
                 permissionNum, umas);  
      
    }// end
  
}// end

void Directory::chmodhelper(int argCount, const char* arguments[])
{
  if (argCount == 1)// if
  {
      cout << "chmod: missing operand" << "\n";
      cout << "Try 'chmod --help' for more information." << "\n";
  }// if
  
  if (argCount == 2)// if
  {
      cout << "chmod: missing operand after ‘" << arguments[1] << "’\n";
      cout << "Try 'chmod --help' for more information." << "\n";
  }// if
  
}// funxtion

void Directory::chmodhelper2(int argCount, const char* arguments[], 
                             int permissionNum, int umas)
{
    
    for (int i = 2; i <= argCount - 1; i++)
    {
        
      int count = 0;
      permissionNum = atoi(arguments[1]);
      
      for (int j = 0; j < subDirectoryCount; j++)
      {
        if (strcmp(subDirectories[j] -> name, arguments[i]) == 0)
        {
          permissionNum = decimalConverter(permissionNum);
          subDirectories[j] -> permissions.set(permissionNum, umas);
          count++;
        }  // if subdirectory exists.
        
      }  // for each subdirectory
      
      if (count < 1)// if
      {
          count = 0;
          cout << "chmod: cannot access ‘" << arguments[i] << "’: ";
          cout << "No such file or directory" << "\n";
          continue;
      }// if
      
    }// loop
    
}// function
      
int Directory::decimalConverter(int octal) // Function to convert
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

void Directory::showPath() const
{
  if (parent == NULL)// parent
  {
    cout << "/";
    return;
  }  // at root
  
  parent->showPath();
  cout << name << "/";
}  // showPath())
