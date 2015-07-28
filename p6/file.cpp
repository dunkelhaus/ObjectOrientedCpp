#include "permissions.h"
#include "file.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

class Directory;

using namespace std;

File::File()
{
  // char* own;
  // strcpy(own, "root");
  // permissions.set(0777, own);
} // no argument constructor

File::File(const File &rhs) : permissions(rhs.permissions)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
} // destructor

File::File(const char *nam, const char *owner)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0666, owner);
} //File

File::~File()
{
  delete [] name;
} // destructor

void File::updateTime()
{
    this->time.update();
} // update time

void File::ls(bool isLongFormat) const
{
  if (isLongFormat)
  {
    time.print();
    cout << name << endl;
  } //if
  else //false
    cout << name << " ";
} // ls

File* File::newFile(File* destinationFile, const char *arguments)
{
  delete [] destinationFile->name;
  destinationFile->name = new char[strlen(arguments) + 1];
  strcpy(destinationFile->name, arguments);
  return destinationFile;
} // createFile()

void File::touch(bool isChangePermission, short permission, const char* user)
{
  if (isChangePermission)
  {
    permissions.chmod(permission, user);
  } //if
  else //not chmod
  {
    updateTime();
  } // else
} // touch

Permissions File::getPermissions() const
{
  return permissions;
}// getpermissions

bool File::operator== (const File &rhs) const
{
  return strcmp(name, rhs.name) == 0;
}  // operator==


bool File::operator< (const File &rhs) const
{
  return strcmp(name, rhs.name) < 0;
}  // operator<

ostream& File::write(ostream &os)
{
  os << this;
  return os;
} //write

istream& File::read(istream &is)
{
  return is;
} //read

ostream& operator<< (ostream &os, File const &rhs)
{
  os << "F" << ' ' << rhs.name << ' ' << rhs.time << ' ' 
     << rhs.permissions << endl;
  return os;
} //friend

istream& operator>> (istream &is, File &rhs)
{
  is >> rhs.name >> rhs.time >> rhs.permissions; 
  is.ignore(10, '\n');
  return is;
}  //friend