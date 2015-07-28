#include <iostream>
#include "permissions.h"
using namespace std;

void Permissions::set(short originalPermissions, short umask)
{
  permissions = originalPermissions & ~umask;
}  // Permissions::set()

void Permissions::print()const
{
  if (permissions & 4)
    cout << "r";
  else  // no read permissions
    cout << "-"; 
  
  if (permissions & 2)
    cout << "w";
  else  // no write permissions
    cout << "-";
  
  if (permissions & 1)
    cout << "x";
  else  // no execute permissions
    cout << "-";
}  // Permissions::print()
