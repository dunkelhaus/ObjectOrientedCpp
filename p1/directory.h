#ifndef DIRECTORY_H
  #define DIRECTORY_H


#include "permissions.h"
#include <stdlib.h>
#include <string.h>

const int MAX_SUBDIRECTORIES = 3;

typedef struct Dir
{
  char *name;
  int time;
  int numOfSubs;
  Dir *subdirectories;
  struct Dir* parentPointer;
  Permissions per;
}Directory; //end of struct definition
 
void createDirectory(Directory *newDirectory, char* name, int time, int umask);
// creates a new directory
char* showPath(Directory *currentDirectory);
// shows the absolute path of a directory recursively
void mkdir(Directory *parentDirectory, char *name, int time, int umask);
// makes new directories and subdirectories
void ls(Directory *currentDirectory, int argCount);
//lists all details a directory
Directory* cd(Directory *currentDirectory, char *name);
//changes directory
#endif
