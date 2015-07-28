#ifndef PERMISSIONS_H
  #define PERMISSIONS_H

#include <cstring>
#include <iostream>
using namespace std;

class Directory;
const int EXECUTE_PERMISSIONS = 1;
const int READ_PERMISSIONS = 4;
const int WRITE_PERMISSIONS = 2;

class Permissions 
{
  short permissions;
public:
  static short umask;
  bool isPermitted(short testedPermission) const;
  void set(short originalPermissions);
  void print() const;
  static void setUmask(int argCount, const char *arguments[]);
  static void umaskOut(ostream &os);
  static void umaskIn(istream &is);
  static short checkOctals(const char *octals);
  void chmod(int argCount, const char *arguments[], Directory* current);
  friend ostream& operator<< (ostream &os, const Permissions &permissions);
  friend istream& operator>> (istream &is, Permissions &permissions);
};  // class Permissions;
#endif  // PERMISSIONS_H

