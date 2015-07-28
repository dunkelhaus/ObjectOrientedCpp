#ifndef PERMISSIONS_H
  #define PERMISSIONS_H

#include <iostream>
using namespace std;

const int EXECUTE_PERMISSIONS = 1;
const int READ_PERMISSIONS = 4;
const int WRITE_PERMISSIONS = 2;

class Permissions 
{
  static short umask;
  short permissions;
  char *owner;
public:
  Permissions();
  Permissions(const Permissions &rhs);
  ~Permissions();
  static short checkOctals(const char *octals);
  void chmod(short newPermissions, const char *user);
  void chown(const char *newOwner);
  bool isPermitted(short testedPermission, const char *user) const;
  void set(short originalPermissions, const char *user);
  void set(Permissions permissions);
  void print() const;
  static void readUmask(istream &is);
  static void setUmask(int argCount, const char *arguments[]);
  static void writeUmask(ostream &os);
  friend ostream& operator<< (ostream &os, const Permissions &permissions);
  friend istream& operator>> (istream &is, Permissions &permissions);
};  // class Permissions;
#endif  // PERMISSIONS_H

