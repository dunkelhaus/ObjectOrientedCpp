#ifndef PERMISSIONS_H
  #define PERMISSIONS_H

#include <iostream>
#include <fstream>
//#include "directory.h"
using namespace std;

class Permissions 
{
public:
  // friend ostream & operator<<(ostream &, const Directory* &);
  int permission1;
  int permission2;
  int permission3;
  int totalPermissions;
  void set(int originalPermissions, int umask);
  friend std::ostream& operator<<(std::ostream& os, const Permissions& perm);
  friend std::istream& operator>>(std::istream& os, const Permissions& perm);
  void print();
  bool isPermitted(int nameBit);
  void printHelper();
  void setHelper(int originalPermissions, int umask, int count);
  // Function to convert octal to decimal
};  // class Permissions;
#endif  // PERMISSIONS_H

