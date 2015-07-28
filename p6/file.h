#ifndef FILE_H
#define	FILE_H

#include "Time.h"
#include "permissions.h"

class Directory; 

using namespace std;

class File
{
  Time time;
protected:
  Permissions permissions;
  char* name;
  void updateTime();
  File* newFile(File* destinationFile, const char *arguments);
public:
  File();
  File(const File &rhs);
  File(const char* nam, const char* owner);
  virtual ~File();
  Permissions getPermissions() const;
  void touch(bool isChangePermission, short permission, const char* user);
  void ls(bool isLongFormat) const;
  bool operator== (const File &rhs) const;
  bool operator< (const File &rhs) const;
  ostream& write(ostream &os);
  istream& read(istream &is);
  friend ostream& operator<< (ostream &os, File const &rhs);
  friend istream& operator>> (istream &is, File &rhs);
}; //File
#endif

