#include <cstring>
#include <iostream>
#include "directory.h"
#include "permissions.h"
#include "list.h"

class File;

using namespace std;

Directory::Directory(const char *nam, Directory *paren, const char *owner)
  : subDirectoryCount(0), parent(paren) 
 {
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, owner);
 }  // Directory())


Directory::Directory(const Directory &rhs) : 
  //subDirectories(rhs.subDirectories), 
  subDirectoryCount(rhs.subDirectoryCount),  
  parent(rhs.parent)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  permissions = rhs.permissions;
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
    
    if (directory) 
      subDirectories += new Directory(*directory);
    else //not directory
      subDirectories += new File(*subDirectories[i]);
  } //end for
  
  for (int i = 0; i < subDirectoryCount; i++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
    
    if (directory)
    directory->parent = this;
  } //end for
}   // Directory copy constructor

int Directory::cdHelper(int argCount, const char *arguments[], 
                        const char *user)
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return 1;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)
  {
    if (parent)
      return 0;
    else  // this is root
      return 1;
  }  // if cd ..

return -1;  
} // cdHelper

Directory* Directory::cd(int argCount, const char *arguments[], 
                         const char *user)
{
  if (cdHelper(argCount, arguments, user) == 1) return this;
  
  if (cdHelper(argCount, arguments, user) == 0) return parent;
  
  for (int i = 0; i < subDirectoryCount; i++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
    
    if (directory)
    {
      if (*subDirectories[i] == Directory(arguments[1]))
      {
        if (subDirectories[i]->getPermissions().isPermitted(EXECUTE_PERMISSIONS
            , user))
        return directory;
        else  // subdirectory doesn't have execute permissions
        {
          cout << arguments[1] << ": Permission denied.\n";
          return this;
        }   // else no execute permissions for the specified directory
      }  // if found the named directory 
    } //end if
    else //not directory
    {
      cout << arguments[1] << ": Not a directory.\n";
      return this;
    } //end else
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()


bool Directory:: iscpCorrectFormat(int argCount, const char *arguments[])
{
  if (argCount != 3)
  {
    if (argCount == 1)
      cout << "cp: missing operand\n";
    else   // more than one argument, but not 3
      if (argCount == 2)
        cout << "cp: missing destination file operand after ‘" << arguments[1]
             << "’\n";
      else  // more than 3 arguments
        cout << "Too many operands\n";

    cout << "Try 'cp --help' for more information.\n";
    return false;
  }  // if incorrect number of operands

  if (strcmp(arguments[1], arguments[2]) == 0)
  {
    cout << "cp: ‘" << arguments[1] << "’ and ‘" << arguments[2]
      << "’ are the same file\n";
    return false;
  }  // if source and destination have the same name

  for (int i = 0; i < subDirectoryCount; i++)
    if (*subDirectories[i] == Directory(arguments[2]))
    {
      cout << "cp: '" << arguments[2] << "' already exists.\n";
      return false;
    }  // if the destination directory already exists

  return true;
}  //  iscpCorrectFormat()


void Directory::chmod(int argCount, const char *arguments[], const char *user)
 // changes the permissions of the arguments
{
  if (chmodH(argCount, arguments, user) == 1) return;
  short newPermissions = Permissions::checkOctals(arguments[1]); int j;
  
  if (newPermissions < 0)
  {
    cout << "chmod: invalid mode: ‘" << arguments[1] << "’\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }  // if invalid permissions
  
  for (int i = 2; i < argCount; i++)
  {
    for (j = 0; j < subDirectoryCount; j++)
    {
      Directory *directory = dynamic_cast<Directory*> (subDirectories[j]);
      
      if (Directory(arguments[i]) == *subDirectories[j])
      {
        if (directory)
          directory->permissions.chmod(newPermissions, user);
        else // not directory
          subDirectories[j]->touch(true, newPermissions, user);
          //subDirectories[j]->getPermissions().chmod(newPermissions, user);
        break;
      }  // if matched name of directory with argument
    } //end for
    
    if (j == subDirectoryCount)
      cout << "chmod: cannot access ‘" << arguments[i] 
           << "’: No such file or directory\n";
  }  // for each filename
}  // chmod()

int Directory::chmodH(int argCount, const char *arguments[], const char *user)
{
  if (argCount < 3)
  {
    if (argCount == 1)
      cout << "chmod: missing operand\n";
    else   // argCount == 2
      cout << "chmod: missing operand after ‘" << arguments[1] << "’\n";

    cout << "Try 'chmod --help' for more information.\n";
    return 1;
  }   // if wrong number of arguments
  
  return 0;
} //forgot


void Directory::chown(int argCount, const char *arguments[])
{
  int j;
  
  if (argCount != 3)
  {
    if (argCount == 1)
      cout << "chown: missing operand\n";
    else  // 2 or more than 3 arguments
      if (argCount == 2)
        cout << "chown: missing operand after ‘" << arguments[1] << "’\n";
      else  // more than 3 arguments
        cout << "chown: Too many arguments.\n";

    cout << "Try 'chown --help' for more information.\n";
    return;
  }  // if wrong number of arguments
  
  for (j = 0; j < subDirectoryCount; j++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[j]);
    
     if (Directory(arguments[2]) == *subDirectories[j])
      {
       
       if (directory)
         directory->permissions.chown(arguments[1]);
        break;
      }  // if matched name of directory with argument
  } //end for 
  
  if (j == subDirectoryCount)
    cout << "chown: cannot access ‘" << arguments[2] 
         << "’: No such file or directory\n";
}  // chown()


void Directory::cp(int argCount, const char *arguments[], const char *user)
{
  if (!  iscpCorrectFormat(argCount, arguments)) return;

  for (int i = 0; i < subDirectoryCount; i++)
    if (*subDirectories[i] == Directory(arguments[1]))
    {
      if (!subDirectories[i]->getPermissions().isPermitted(READ_PERMISSIONS
          , user ))
      {
        cout << "cp: cannot open ‘" << arguments[1] 
             << "’ for reading: Permission denied\n"; return;
      }  // if not allowed to read
      
      Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
      
      if (directory)
      {
        Directory *destinationDirectory = new Directory(*directory);
        delete [] destinationDirectory->name;
        destinationDirectory->name = new char[strlen(arguments[2]) + 1];
        strcpy(destinationDirectory->name, arguments[2]);
        subDirectories += destinationDirectory;
        subDirectoryCount++; return;
      }//end if
      
      else //not directory
      {
        File *destinationFile = new File(*subDirectories[i]);
        subDirectories += newFile(destinationFile, arguments[2]);
        subDirectoryCount++; return;
      } //end else
    }  // if found source subdirectory
  
  printCpError(arguments);
}  // cp())

void Directory::printCpError(const char* arguments[])
{
   cout << "cp: cannot stat ‘" << arguments[1] 
       << "’: No such file or directory\n";
  cout << "Try 'cp --help' for more information.\n";
} // printcperror

void Directory::ls(int argCount, const char *arguments[], const char *user)const
{
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]\n";
  else  // correct number of arguments
  {
    if (permissions.isPermitted(READ_PERMISSIONS, user))
    {
      if (argCount == 1)  // simple ls
      {
        for (int i = 0; i < subDirectoryCount; i++)
          subDirectories[i]->ls(false);
          //cout << subDirectories[i]->name << " ";

        cout << "\n";
      }  // if simple ls
      else  // must be ls -l
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          subDirectories[i]->getPermissions().print();
          cout << ' ';
          subDirectories[i]->ls(true);
          //subDirectories[i]->printTime();
          //cout << subDirectories[i]->name << endl;
        }  // for each subdirectory
      }  // else is ls -l
    }  // if have read permissions
    else // don't have read permissions
      cout << "ls: cannot open directory .: Permission denied\n";
  }  // else correct arguments
}  // ls()


void Directory::mkdir(int argCount, const char *arguments[], const char *user)
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
      if (*subDirectories[i] == Directory(arguments[argPos]))
      {
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             << "’: File exists\n"; 
        break;
      }  // if subdirectory already exists.
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS, user))
      {
        subDirectories += new Directory(arguments[argPos], this, user);
        updateTime();
        subDirectoryCount++;
      }  // if have write permissions
      else // no write permissions
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             <<  "’: Permission denied\n";
    }  // if name not found
  }  // for each filename
}  // mkdir()


void Directory::touch(int argCount, const char *arguments[], const char *user)
{
  int i;
  
  if (argCount == 1)
  {
    cout << "touch: missing operand\n";
    cout << "Try 'touch --help' for more information.\n";
    return;
  }  // if too many arguments
   
  for (int argPos = 1; argPos < argCount; argPos++)
  {
    for (i = 0; i < subDirectoryCount; i++)
      if (*subDirectories[i] == Directory(arguments[argPos]))
      {
        subDirectories[i]->touch(false, 0, "fake");
        break;
      }  // if file already exists.
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS, user))
      {
        subDirectories += new File(arguments[argPos], user);
        updateTime();
        subDirectoryCount++;
      }  // if have write permissions
      else // no write permissions
        cout << "touch: cannot create file ‘" << arguments[argPos] 
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

ostream& Directory::write(ostream &os, int dummy)
{
  os << "D";
  File::write(os); 
  // os << ' ' << subDirectoryCount;
  
  for (int i = 0; i < subDirectoryCount; i++)
    os << *subDirectories[i];
  return os;
} //write

istream& Directory::read(istream &is, Directory &rhs)
{
  is >> rhs.subDirectoryCount; 
  is.ignore(10, '\n');
  
  for (int i = 0; i < rhs.subDirectoryCount; i++)
  {
    Directory *subDirectory = new Directory("Dummy", &rhs);
    is >> *subDirectory;
    rhs.subDirectories += subDirectory;
  }  // for each subdirectory
  
  return is;
} //read