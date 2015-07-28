#ifndef PERMISSIONS_H
  #define PERMISSIONS_H

class Permissions 
{
  short permissions;
public:
  void set(short originalPermissions, short umask);
  void print()const;
}; // class Permissions
#endif  // PERMISSIONS_H

