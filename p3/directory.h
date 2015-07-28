#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include "permissions.h"

const int MAX_DIRECTORIES = 3;

class Directory
{
  char* name;
  int time;
  Directory** subDirectories;
  int subDirectoryCount;
  Directory* parent;
  Permissions permissions;
public:
  Directory( const char *name, short umask, int time, Directory *parent);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  void ls(int argCount, const char *arguments[])const;
  void mkdir(int argCount, const char *arguments[], 
             short umask, int time);
  void showPath()const;
}; // class Directory

#endif  // DIRECTORY_H