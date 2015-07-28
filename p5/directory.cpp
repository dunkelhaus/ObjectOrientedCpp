#include <cstring>
#include <iostream>
#include "directory.h"
using namespace std;

Directory::Directory(const char *nam, Directory *paren)
  : parent(paren), subDirectories(NULL), subDirectoryCount(0)
 {
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777);
  subDirectories = new List();
  
 }  // Directory())


Directory::~Directory()
{
  delete [] name;
 
  //for (int i = 0; i < subDirectoryCount; i++)
    //delete subDirectories[i];

  delete subDirectories;
}  // ~Directory()


void Directory::addDirectory(const char *nam)
{
  *subDirectories += new Directory(nam, this);
  subDirectoryCount++;
  time.update();
}  // addDirectory())

Directory* Directory::cd(int argCount, const char *arguments[])
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName\n";
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
    if (*(*subDirectories)[i] == Directory(arguments[1]))
    {
      if ((*subDirectories)[i]->permissions.isPermitted(EXECUTE_PERMISSIONS))
        return (*subDirectories)[i];
      else  // subdirectory doesn't have execute permissions
      {
        cout << arguments[1] << ": Permission denied.\n";
        return this;
      }   // else no execute permissions for the specified directory
    }  // if found the named directory 
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()

void Directory::ls(int argCount, const char *arguments[])const
{
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]\n";
  else  // correct number of arguments
  {
    if (permissions.isPermitted(READ_PERMISSIONS))
    {
      if (argCount == 1)  // simple ls
      {
        for (int i = 0; i < subDirectoryCount; i++)
          cout << (*subDirectories)[i]->name << " ";

        cout << "\n";
      }  // if simple ls
      else  // must be ls -l
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          (*subDirectories)[i]->permissions.print();
          cout << ' ';
          (*subDirectories)[i]->time.print();
          cout << (*subDirectories)[i]->name << endl;
        }  // for each subdirectory
      }  // else is ls -l
    }  // if have read permissions
    else // don't have read permissions
      cout << "ls: cannot open directory .: Permission denied\n";
  }  // else correct arguments
}  // ls()


void Directory::mkdir(int argCount, const char *arguments[])
{
  int i;
  
  if (argCount == 1)
  {
    cout << "mkdir: missing operand\n";
    cout << "Try 'mkdir --help' for more information.\n";
    return;
  }  // if too many arguments
   
  for (int argPos = 1; argPos < argCount; argPos++)
  {
    for (i = 0; i < subDirectoryCount; i++)
      if (*(*subDirectories)[i] == Directory(arguments[argPos]))
      {
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             << "’: File exists\n"; 
        break;
      }  // if subdirectory already exists.
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS))
      {
        addDirectory(arguments[argPos]);
      }  // if there are write permissions
      else // no write permissions
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             <<  "’: Permission denied\n";
    }  // if name not found
  }  // for each filename
}  // mkdir()


void Directory::showPath() const
{
  if (parent == NULL)
  {
    cout << "/";
    return;
  }  // at root
  
  parent->showPath();
  cout << name << "/";
}  // showPath())

void Directory::cp(int argCount, const char *arguments[])
{
  if (hasCpHelper(argCount, arguments)) 
  {
    int j;
  
    for (int i = 2; i < argCount; i++)
    {
      for (j = 0; j < subDirectoryCount; j++)
        if (Directory(arguments[1]) == *(*subDirectories)[j]) 
        {
          Directory *temp = new Directory(*(*subDirectories)[j]);
          temp->name = new char [strlen(arguments[2]) + 1];
          strcpy(temp->name, arguments[2]); *subDirectories += temp; 
          subDirectoryCount++; break;
        }  // if name of directory matches with argument
        else // name of directory does not match with argument
        {
          cout << "cp: cannot stat ‘" << arguments[1];
          cout << "’: No such file or directory" << endl;
          cout << "Try 'cp --help' for more information." << endl; return;
        } // name of directory does not match with argument
    
      if (j == subDirectoryCount)
      {
        cout << "cp: cannot access ‘" << arguments[i];
        cout << "’: No such file or directory" << endl; return;
      } // j is subDirectoryCount
    
    }  // for each filename
    
  } // if correct cp 
  
} //cp()

bool Directory::hasCpHelper(int argCount, const char *arguments[])
{
  
   if (argCount == 1)
   {
    cout << "cp: missing operand" << endl;
    cout << "Try 'cp --help' for more information.\n"; return false;
   }  // argCount is 1
  
  if ( argCount == 2)
  {
    cout << "cp: missing destination file operand after ‘" << arguments[1];
    cout << "’";
    cout << endl;
    cout << "Try 'cp --help' for more information.\n"; return false;
  } // argCount is 2
  
  if (argCount > 3)
  {
    cout << "Too many operands\nTry 'cp --help' for more information.\n";
    return false;
    
  } // if argCount is more than 3
  
  if (subDirectoryCount == 0)
  {
    cout << "cp: cannot stat ‘" << arguments[1];
    cout << "’: No such file or directory";
    cout << endl;
    cout << "Try 'cp --help' for more information.\n"; return false;
  } // subDirectoryCount is 0
   
   return true;
   
} //cpHelper()

bool Directory::operator== (const Directory &rhs) const
{
  return strcmp(name, rhs.name) == 0;
}  // operator==

bool Directory::operator<(const Directory &rhs) const
{
  return strcmp(name, rhs.name) < 0;
} //operator<


ostream& operator<< (ostream &os, Directory const &rhs)
{
  os << rhs.name << ' ' << rhs.time << ' ' << rhs.subDirectoryCount << ' '
     << rhs.permissions << endl;
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
  // for (int i = rhs.subDirectoryCount - 1; i > -1; i--)
    os << *(*rhs.subDirectories)[i];
  return os;
}  // operator<<

istream& operator>> (istream &is, Directory &rhs)
{
  is >> rhs.name >> rhs.time >> rhs.subDirectoryCount >> rhs.permissions;
  is.ignore(10, '\n');
  
  //(*rhs.subDirectories) = new Directory*[rhs.subDirectoryCount];
  (rhs.subDirectories) = new List;
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
  {
    //*rhs.subDirectories =+ new Directory("Dummy", 0, &rhs);
    Directory *temp = new Directory("*l", &rhs);
    *rhs.subDirectories += temp;
    is >> *(*rhs.subDirectories)[0];
  }  // for each subdirectory
  
  return is;
}  // operator>>