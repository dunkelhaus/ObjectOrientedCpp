#include <iostream>
#include <cstring>
#include "permissions.h"
#include "directory.h"
using namespace std;

short Permissions::umask = 022;

bool Permissions::isPermitted(short testedPermission) const
{
  return ((permissions >> 6) & testedPermission) == testedPermission;
}  // isPermitted()


void Permissions::set(short originalPermissions)
{
  permissions = originalPermissions & ~umask;
}  // set())


void Permissions::print() const
{
  for (int i = 6; i >= 0 ; i -= 3)
  {
    if ((permissions >> i) & 4)
      cout << "r";
    else  // no read permissions
      cout << "-";

    if ((permissions >> i) & 2)
      cout << "w";
    else  // no write permissions
      cout << "-";

    if ((permissions >> i) & 1)
      cout << "x";
    else  // no execute permissions
      cout << "-";
  }  // for each set of rwx permissions
}  // print()

short Permissions::checkOctals(const char *octals)
{
  short newPermissions = 0;
  
  if (strlen(octals) > 4)
  {
     cout << "chmod: invalid mode: ‘" << octals << "’\n";
     cout << "Try 'chmod --help' for more information.\n";
    return -1;
  }  // if umask value too long.
  
  for (int i = 0; octals[i] != '\0'; i++ )
    if (octals[i] < '0' || octals[i] > '7')
    {
      cout << "chmod: invalid mode: ‘" << octals << "’\n";
      cout << "Try 'chmod --help' for more information.\n";
      return -1;
    }  // if incorrect octal
    else  // valid octal digit
      newPermissions = newPermissions * 8 + octals[i] - '0';
  
  return newPermissions;
}  // checkOctals())

void Permissions::setUmask(int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{
  short newUmask = 0;
  
  if (argCount == 1)
  {
    cout << oct << umask << dec << endl;
    return;
  }  // if only "umask" on commandline
  
  if (argCount != 2)
  {
    cout << "umask: Too many arguments.\n";
    return;
  }  // if more than 2 arguments
  
  
  if (strlen(arguments[1]) > 3)
  {
    cout << "umask: Improper mask.\n";
    return;
  }  // if umask value too long.
  
  for (int i = 0; arguments[1][i] != '\0'; i++ )
  {
    if (arguments[1][i] < '0' || arguments[1][i] > '7')
    {
      cout << "umask: Improper mask.\n";
      return;
    }  // if incorrect octal
    else  // valid octal digit
      newUmask = newUmask * 8 + arguments[1][i] - '0';
  }   // for each digit in argument
  
  umask = newUmask;
}  // umask()

ostream& operator<< (ostream &os, const Permissions &permissions)
{
  os << permissions.permissions;
  return os;
}  // operator<<


istream& operator>> (istream &is, Permissions &permissions)
{
  is >> permissions.permissions;
  return is;
} // operator>>

void Permissions::umaskOut(ostream &os)
{
    os << umask;
}

void Permissions::umaskIn(istream &is)
{
    is >> umask;
}

void Permissions::chmod(int argCount, const char *arguments[],
                        Directory* current)
 // changes the permissions of the arguments
{
  int j;
  
  if (argCount == 1)
  {
    cout << "chmod: missing operand\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }  // if only "chmod"
  
  if (argCount == 2)
  {
    cout << "chmod: missing operand after ‘" << arguments[1] << "’\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }   // if only "chmod octals"
  
  short newPermissions = checkOctals(arguments[1]);
  
  if (newPermissions < 0)
    return;
  
  for (int i = 2; i < argCount; i++)
  {
    for (j = 0; j < current -> subDirectoryCount; j++)
      if (Directory(arguments[i]) == *(*(current -> subDirectories))[j])
      {
        (*(current -> subDirectories))[j]->permissions.umask = 0;
        (*(current -> subDirectories))[j]->permissions.set(newPermissions);
        break;
      }  // if matched name of directory with argument
    
    if (j == current -> subDirectoryCount)
      cout << "chmod: cannot access ‘" << arguments[i] 
           << "’: No such file or directory\n";
  }  // for each filename
}  // chmod())
