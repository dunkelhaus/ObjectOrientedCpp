#include <cstring>
#include <iostream>
#include <cstdlib>
#include "directory.h"
using namespace std;
        
Directory::Directory( const char *nam, short umas, int tim, Directory *paren)
        : time(tim), subDirectories(NULL), subDirectoryCount(0), parent(paren)
 // createDirectory())
{ 
  name = new char [strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(7, umas);
}// object maker

Directory::~Directory()
{
  if (subDirectories) 
    delete [] subDirectories;
    
  if (name)
    delete [] name;
    
  if (parent)
    delete parent;
}// object deletor
Directory* Directory::cd(int argCount, const char *arguments[])
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName" << "\n"; 
    return this;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)
  {
    if (parent)
      return parent;
    else  // this is root
      return this;
  }  // if cd ..

  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (strcmp(subDirectories[i]->name, arguments[1]) == 0)
      return subDirectories[i]; // removed address operator
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory" << "\n"; 
  return this;
}  // cd()

void Directory::ls(int argCount, const char *arguments[])const
{
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]" << "\n";
  else  // correct number of arguments
  {
    if (argCount == 1)  // simple ls
    {
      for (int i = 0; i < subDirectoryCount; i++)
        cout << subDirectories[i]->name << " "; //changed
      
       cout << "\n";
    }  // if simple ls
    else  // must be ls -l
    {
      for (int i = 0; i < subDirectoryCount; i++)
      {
        subDirectories[i]->permissions.print(); // changed
        cout << " " << subDirectories[i]->time << " ";
        cout << subDirectories[i]->name << "\n"; // chnaged
      }  // for each subdirectory
    }  // else is ls -l
  }  // else correct arguments
}  // ls()


void Directory::mkdir
(int argCount, const char *arguments[], short umask, int time)
{
  if (argCount != 2)
  {
    cout << "usage: mkdir directory_name" << "\n"; 
    return;
  }  // if too many arguments
  
  if (subDirectoryCount == MAX_DIRECTORIES)
  {
    cout << "mkdir: " << name 
            << " already contains the maximum number of directories" << "\n"; 
    return;
  }  // if already at max subdirectories
  
  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (strcmp(subDirectories[i]->name, arguments[1]) == 0)//changed
    {
      cout << "mkdir: cannot create directory '" << arguments[1] << "':" << 
              " File exists" << "\n"; 
      return;
    }  // if subdirectory already exists.
  }  // for each subdirectory
  
  Directory **subDirectoriesTemp = new Directory*[subDirectoryCount + 1]; 
    
  for (int i = 0; i < subDirectoryCount; i++)
    subDirectoriesTemp[i] = subDirectories[i];
  
  if (subDirectories)
    delete [] subDirectories;
  subDirectoriesTemp[subDirectoryCount] = 
          new Directory(arguments[1], umask, time, this);
  subDirectories = subDirectoriesTemp;
  subDirectoryCount++; 
}  // mkdir()

void Directory::showPath()const
{
  if (parent == NULL)
  {
    cout << "/";
    return;
  }  // at root
  
  parent->showPath();
  cout << name << "/";
}  // showPath())
