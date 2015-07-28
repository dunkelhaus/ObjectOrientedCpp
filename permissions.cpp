#define PERMISSIONS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "directory.h"
#include "funix.h"

void showPermissions(short OctalPermission)
{

  switch(OctalPermission)
  {
    case 0:
      printf("rwx ");
    break;
    case 1:
      printf("rw- ");
    break;
    case 2:
      printf("r-x ");
    break;
    case 3:
      printf("r-- ");
    break;
    case 4:
      printf("-wx ");
    break;
    case 5:
      printf("-w- ");
    break;
    case 6:
      printf("--x ");
    break;
    case 7:
      printf("--- ");
    break;
  }// switch(OctalPermission)

}// void showPermissions(short OctalPermission)

