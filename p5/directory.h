#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "iostream"
#include "permissions.h"
#include "Time.h"
#include "list.h"
using namespace std;

class Directory
{
  char *name;
  Time time;
  Directory *parent;
  void addDirectory(const char *nam);
  short checkOctals(const char *octals) const;
public:
  Permissions permissions;
  List *subDirectories;
  int subDirectoryCount;
  Directory(const char *nam, Directory *paren = NULL);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  /*void chmod(int argCount, const char *arguments[]);*/
    // changes the permissions of the arguments
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[]);
  void cp(int argCount, const char *arguments[]);
  bool hasCpHelper(int argCount, const char *arguments[]);
  void showPath() const;
  bool operator== (const Directory &rhs) const;
  bool operator<(const Directory &rhs) const;
  friend ostream& operator<< (ostream &os, Directory const &rhs);
  friend istream& operator>> (istream &is, Directory &rhs);
};  // class Directory
#endif  // DIRECTORY_H
