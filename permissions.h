#ifndef PERMISSION_H
#define PERMISSION_H
typedef struct 
{
  short octalPermission;
}Permissions; // end of struct definition



void showPermissions(short OctalPermission);
//prints the permissions of a directory
#endif
