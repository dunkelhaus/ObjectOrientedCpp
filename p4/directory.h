#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_DIRECTORIES = 3;

class Directory
{
  Directory *parent;
public:
  char *name;
  Permissions permissions;
  Time time;
  int subDirectoryCount;
  int umask;
  Directory **subDirectories;
  // friend ostream & operator<<(ostream &, const Directory* &);
  Directory(const char *nam, int umas, Directory *paren);
  Directory(const char *nam);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  bool operator==(const Directory& dir1) const;
  void looper(int argCount, const char *arguments[]);
  void mkdirhelper(int argCount, const char* arguments[], int umas);
  void mkdirhelper2(const char* arguments[], int umas, int i);
  friend ostream& operator<<(ostream& outf, const Directory& directory);
  friend istream& operator>>(istream& inf, const Directory& directory);
  void ls(int argCount, const char *arguments[]);
  void mkdir(int argCount, const char *arguments[], int umas);
  void chmod(int argCount, const char *arguments[], int umas);
  void chmodhelper(int argCount, const char* arguments[]);
  void chmodhelper2(int argCount, const char* arguments[], 
                    int permissionNum, int umas);
  int decimalConverter(int octal); // Function to convert octal to decimal 
  void showPath() const;
};  // class Directory
#endif  // DIRECTORY_H

