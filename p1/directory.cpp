#define DIRECTORY_H


#include "directory.h"
#include "permissions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SUBDIRECTORIES 3

typedef struct Dir
{
  char *name;
  int time;
  int numOfSubs;
  Dir *subdirectories;
  struct Dir* parentPointer;
  Permissions per;
}Directory; // Directory struct

void createDirectory(Directory *newDirectory, char* name, int time, int umask)
{
  newDirectory -> name = (char *)malloc(sizeof(char)* 80);
  strcpy(newDirectory -> name, name);
  newDirectory -> per.octalPermission = umask;
  newDirectory -> time = time;
  newDirectory -> subdirectories = (Directory *)malloc(sizeof(Directory) * MAX_SUBDIRECTORIES);
}// createDirectory()
void showPath(Directory *currentDirectory)
{
  char* name2 = (char *)malloc(sizeof(char) * MAX_SUBDIRECTORIES);
  strcpy(name2, "/");

  if (strcmp(currentDirectory -> name, name2) == 0)//checks root
  {
    ;
  }// if(strcmp(currentDirectory -> name, name2) == 0)

  else //recurses
  {
    showPath(currentDirectory -> parentPointer); // path
    printf("/%s", currentDirectory -> name);
  }// else
}// void showPath(Directory *currentDirectory)
void mkdir(Directory *parentDirectory, char *name, int time, int umask)
{

  switch(parentDirectory -> numOfSubs)
  {

    case 2:// if they are 2 subdirectories already created
    {

      if (strcmp((parentDirectory -> subdirectories[0]).name, name) == 0)// name
      {
        printf("mkdir: cannot create directory '%s': File exists\n", name);
        return;
        break;
      }// if(strcmp((parentDirectory -> subdirectories[0]).name, name) == 0)

      else if (strcmp((parentDirectory -> subdirectories[1]).name, name) == 0)//name
      {
        printf("mkdir: cannot create directory '%s': File exists\n", name);
        return;
        break;
      }// else if()
    }// case 2:

    case 1:// if there is just one subdirectory created
    {
      //checks if name is repeating
      if (strcmp((parentDirectory -> subdirectories[0]).name, name) == 0)
      {
         printf("mkdir: cannot create directory '%s': File exists\n", name);
         return;
         break;
      }// if(strcmp((parentDirectory -> subdirectories[0]).name, name) == 0)

      break;
    }// case 1:

    case 0:
    {
      ;
      break;
    }// case 0:

    default:
    {
      break;
    }// default:

  }// switch

  Directory *newDirectory = (Directory *)malloc(sizeof(Directory));
  createDirectory(newDirectory, name, time, umask);
  newDirectory -> parentPointer = parentDirectory;


  if (((parentDirectory -> numOfSubs) + 1) <= MAX_SUBDIRECTORIES)// subD <= 3
  {
    parentDirectory -> subdirectories[(parentDirectory -> numOfSubs)] = *(newDirectory);
    parentDirectory -> numOfSubs += 1;
    newDirectory -> time = time;
  }// if (((parentDirectory -> numOfSubs) + 1) <= 3)
  else // the number of subdirectories exceed 3 
  {
    printf("mkdir: %s already contains maximum number of subdirectories\n", parentDirectory -> name);
  }// else

  free(newDirectory -> subdirectories);
} // void mkdir(Directory *parentDirectory, char *name, int time, int umask)
void ls(Directory *currentDirectory, int argCount)
{
  int numOfLines = currentDirectory -> numOfSubs;

  if (argCount == 1)// when command is ls-l
  {
    int i = 0;

    for (i = 0; i < numOfLines; i++)
    {
        showPermissions((currentDirectory -> subdirectories[i]).per.octalPermission);
        printf("%d ", (currentDirectory -> subdirectories[i].time) + 1);
        printf("%s \n", currentDirectory -> subdirectories[i].name);
    }// for(i = 0; i < numOfLines; i++)
  }// if(argCount == 1)

  if (argCount == 0)// when command is ls
  {
    int i = 0;

    for (i = 0; i < numOfLines; i++)
    {

      if (i == (numOfLines - 1))// printing spaces
      {
        printf("%s", currentDirectory -> subdirectories[i].name);
      }

      else //printing spaces
      {
        printf("%s ", currentDirectory -> subdirectories[i].name);
      }

    }// for(i = 0; i < numOfLines; i++)

    printf("\n");
  }// if (argCount == 0)
}// void ls(Directory *currentDirectory, int argCount)
Directory* cd(Directory *currentDirectory, char *name)
{
  switch(currentDirectory -> numOfSubs)//number of subdirectories
  {
    case 3:// 3 subdirectories are present
    {

      //checks the name of first subdirectory
      if (strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)
      {
        currentDirectory = &(currentDirectory -> subdirectories[0]);
        return currentDirectory;
      }//  if(strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)

      //checks name of second subdirectory
      else if (strcmp((currentDirectory -> subdirectories[1]).name, name) == 0)
      {
        currentDirectory = &(currentDirectory -> subdirectories[1]);
        return currentDirectory;
      }// else if(strcmp((currentDirectory -> subdirectories[1]).name, name) == 0)

      //checks name of third subdirectory
      else if (strcmp((currentDirectory -> subdirectories[2]).name, name) == 0)
      {
        currentDirectory = &(currentDirectory -> subdirectories[2]);
        return currentDirectory;
      }// else if(strcmp((currentDirectory -> subdirectories[2]).name, name) == 0)

      else if (strcmp(name, "..") == 0)// checks if '..' is entered
      {
        
        if (currentDirectory -> parentPointer == NULL)// checks if parent directory
        {
          return currentDirectory;
        }// if(currentDirectory -> parentPointer == NULL)

        currentDirectory = currentDirectory -> parentPointer;
        return currentDirectory;
      }// else if(strcmp(name, "..") == 0)
      else // if something else other than proper syntax is entered
      {
        printf("cd: %s: No such file or directory\n", name);
        return currentDirectory;
      }// else

      break;
    }// case 3:

    case 2:// two subdirectories are present
    {

      if (strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)// if name entered matches 1st subdirectory
      {
        currentDirectory = &(currentDirectory -> subdirectories[0]);
        return currentDirectory;
      }// if(strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)

      else if (strcmp((currentDirectory -> subdirectories[1]).name, name) == 0)// if name entered matches the 2nd directory
      {
        currentDirectory = &(currentDirectory -> subdirectories[1]);
        return currentDirectory;
      }// else if(strcmp((currentDirectory -> subdirectories[1]).name, name) == 0)

      else if (strcmp(name, "..") == 0)// if ".." is entered
      {

        if (currentDirectory -> parentPointer == NULL)// checks if its the parent directory
        {
          return currentDirectory;
        }// if(currentDirectory -> parentPointer == NULL)

        currentDirectory = currentDirectory -> parentPointer;
        return currentDirectory;
      }// else if(strcmp(name, "..") == 0)

      else // if something other than the correct syntax is entered
      {
        printf("cd: %s: No such file or directory\n", name);
        return currentDirectory;
      }// else

      break;
    }// case 2:

    case 1://one subdirectory is present
    {
      
      if (strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)// if name entered matches the 1st subdirectory
      {
        currentDirectory = &(currentDirectory -> subdirectories[0]);
        return currentDirectory;
      }// if (strcmp((currentDirectory -> subdirectories[0]).name, name) == 0)

      else if (strcmp(name, "..") == 0)// if ".." is entered
      {
        
        if (currentDirectory -> parentPointer == NULL)// checks if its the parent directory
        {
          return currentDirectory;
        }// if(currentDirectory -> parentPointer == NULL)

        currentDirectory = currentDirectory -> parentPointer;
        return currentDirectory;

      }// else if(strcmp(name, "..") == 0)

      else // if something other than correct syntax is entered
      {
        printf("cd: %s: No such file or directory\n", name);
        return currentDirectory;
      }// else

      break;
    }// case 1:

    case 0:// no subdirectories present
    {

      if (strcmp(name, "..") == 0)// if ".." is entered
      {

        if (currentDirectory -> parentPointer == NULL)// checks if it its the parent directory
        {
          return currentDirectory;
        }// if(currentDirectory -> parentPointer == NULL)

        currentDirectory = currentDirectory -> parentPointer;
        return currentDirectory;
      }// if(strcmp(name, "..") == 0)

      else //if something other than correct syntax is entered
      {
        printf("cd: %s: No such file or directory\n", name);
        return currentDirectory;
      }// else

      break;
    }// case 0:

    default:
    {
      printf("cd: %s: No such file or directory\n", name);
      break;
    }// default:

  }// switch()

 return currentDirectory;
}// cd()
