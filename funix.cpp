#define FUNIX_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"
#include "funix.h"
#include "permissions.h"

#define COMMAND_LENGTH 80

typedef struct
{
  Directory *currentDirectory;
  int umask;
  int time;
}Funix; // Funix struct

void cd(Funix *funix, int argCount, const char *arguments[])
{
  char* name = (char *)malloc(sizeof(char) * COMMAND_LENGTH);
  strcpy(name, arguments[0]);
  funix -> currentDirectory = cd(funix -> currentDirectory, name);
}// cd()

int eXit(Funix *funix, int argCount, const char *arguments[])
{
  exit(0);
  return 0;
}// exit()

void writePrompt(Funix *funix)
{
   showPath(funix -> currentDirectory);
   printf("/ # ");
}// writePrompt()

void getCommand(Funix *funix, char *command)
{
  free(command);
  command = (char *)malloc(sizeof(char) * COMMAND_LENGTH);
  char command2[80];
  writePrompt(funix);
  fgets(command2, 80, stdin);
  int i = 0;
  
  while(command2[i] != '\n')
  {
    i++;
  }// while

  strcpy(command, command2);
  command[i] = '\0';
}// getCommand()

void init(Funix *funix)
{
  Directory *temp;
  temp = (Directory *)malloc(sizeof(Directory));
  char* name = (char *) malloc(sizeof(char) * 3);
  strcpy(name, "/");
  createDirectory(temp, name, 0, 0);
  funix -> currentDirectory = temp;
}// init()

void ls(Funix *funix, int argCount, const char *arguments[])
{
  ls(funix -> currentDirectory, argCount);
}// ls()

void mkdir(Funix *funix, int argCount, const char *arguments[])
{
  char* name = (char *)malloc(sizeof(char) * COMMAND_LENGTH);
  strcpy(name, *(arguments));
  mkdir(funix -> currentDirectory, name, (funix -> time) - 1, funix -> umask);
}// mkdir()

int processCommand(Funix *funix, char *command);

void run(Funix *funix)
{
  init(funix);
  int returnValue = 1;
  char* command = (char *)malloc(sizeof(char) * COMMAND_LENGTH);
  int i = 0;
  
  while(returnValue != 0)
  {
    getCommand(funix, command);
    (funix ->time)++; 
    returnValue = processCommand(funix, command);
    i++;
  }// while loop

}// run()

void umask(Funix *funix, int argCount, const char *arguments[])
{
  funix -> umask = argCount;
  (funix -> currentDirectory -> per).octalPermission = argCount;
}// umask()
int processCommand(Funix *funix, char *command)
{
  char* commandCopy;
  char* commandCopy2;
  int inputLength = strlen(command);
  
  if (inputLength == 0)// in case empty string entered from terminal
  {
    return 1;
  }// if

  commandCopy = (char *)malloc(sizeof(char) * (inputLength));
  commandCopy2 = (char *)malloc(sizeof(char) * (inputLength));
  strncpy(commandCopy, command, inputLength);
  strncpy(commandCopy2, commandCopy, inputLength);
  char* token; 
  token = strtok(commandCopy, " "); // first word of command
  int tokenNumber = 0;
  int wordCount = 0;
  
  if (strcmp(token, "cd") == 0)// compares token to "cd"
  {
    tokenNumber = 1;
  }// if

  else if (strcmp(token, "mkdir") == 0)// compares token to "mkdir"
  {
    tokenNumber = 2;
  }// else if

  else if (strcmp(token, "ls") == 0)// compares token to "ls"
  {
    tokenNumber = 3;
  }// else if
 
  else if (strcmp(token, "umask") == 0)// compares token to "umask"
  {
    tokenNumber = 4;
  }// else if

  else if (strcmp(token, "exit") == 0)// compares token to "exit"
  {
    tokenNumber = 5;
  }// else if

  switch(tokenNumber)
  {
    
    case 1:
    {
      const char* token2;
      
      while (token != NULL)
      {
        wordCount++;
        token = strtok (NULL, " ");
      }// while
      
      if (wordCount > 2)// when there's more than 2 words
      {
        printf("usage: cd directoryName\n");
        return 1;
        break;
      }// if(wordCount > 2)
      
      if (wordCount < 2)// when there's less than 2 words
      {
        printf("usage: cd directoryName\n");
        return 1;
        break;
      }// if(wordCount > 2)
      
      token2 = strtok(commandCopy2, " ");
      token2 = strtok(NULL, " ");
      const char* tokenArray[10];
      tokenArray[0] = token2;
      cd(funix, 0, tokenArray);
      return 1;
      break;
    }// case 1:
    
    case 2:
    {
      const char* token2;
      
      while (token != NULL)
      {
        wordCount++;
        token = strtok (NULL, " ");
      }// while (token != NULL)
      
      if (wordCount > 2)// when there's more than 2 words
      {
        printf("usage: mkdir directory_name\n");
        return 1;
        break;
      }// if(wordCount > 2)
      
      if (wordCount < 2)
      {
        printf("usage: mkdir directory_name\n");
        return 1;
        break;
      }// if(wordCount < 2)

      token2 = strtok(command, " ");
      token2 = strtok(NULL, " ");
      const char* tokenArray[10];
      tokenArray[0] = token2;
      mkdir(funix, 0, tokenArray);
      return 1;
      break;
    }// case 2:
    
    case 3:
    {
      
      while (token != NULL)
      {
        wordCount++;
        token = strtok (NULL, " ");
      }// while (token != NULL)
      
      if (wordCount == 1)// when there is only one word i.e. ls
      {
        ls(funix, 0, NULL);
        return 1;
        break;
      }// if(wordCount == 1)
      
      if (strcmp(commandCopy2, "ls -l") != 0)// more words
      {
        printf("usage: ls [-l]\n");
        return 1;
        break;
      }// if(strcmp(commandCopy2, "ls -l") != 0)
 
      ls(funix, 1, NULL);
      return 1;
      break;
    }// case 3:
    
    case 4:
    {
      int octal = 0;
      char* token2;
      
      while (token != NULL)
      {
        wordCount++;
        token = strtok (NULL, " ");
      }// while (token != NULL)
      
      if (wordCount > 2)// when there are more than 2 words in command
      {
        printf("usage: umask octal\n");
        return 1;
        break;
      }// if(wordCount > 2)
      
      if (wordCount < 2)// when there are less than 2 words in command
      {
        printf("usage: umask octal\n");
        return 1;
        break;
      }// if(wordCount < 2)
 
      token2 = strtok(commandCopy2, " ");
      token2 = strtok (NULL, " ");
      octal = atoi(token2);
      
      if (octal == 0)// when octal is 0
      {
        
        if (strcmp(token2, "0") != 0)//checks atoi to string
        {
          printf("usage: octal must be between 0 and 7\n");
          return 1;
          break;
        }// if (strcmp(token2, "0") != 0)
      }// (octal == 0)
      
      if (octal < 0 || octal > 7)// when octal is not between 0 and 7
      {
        printf("usage: octal must be between 0 and 7\n");
        return 1;
        break;
      }// if(octal < 0 || octal > 7)

      umask(funix, octal, NULL);
      return 1;
      break;
    }// case 4:
    
    case 5:
    {
      
      while (token != NULL)
      {
        wordCount++;
        token = strtok (NULL, " ");
      }// while (token != NULL)
      
      if (wordCount > 1)// when more than one word entered with exit
      {
        printf("usage: exit\n");
        return 1;
        break;
      }// if (wordCount > 1)

      eXit(funix, 0, NULL);
      return 0;
      break;
    }// case 5:
    
    default:
    {
      printf("%s: Command not found.\n", command);
      return 1;
      break;
    }// default:

  }// switch

  free(commandCopy);
  free(commandCopy2);
  return 1;
}// processCommand()

