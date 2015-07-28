

#include <iostream>
#include <cmath>
#include <fstream>
#include "permissions.h"
using namespace std;

std::ostream& operator<<(std::ostream& os, const Permissions& perm)
{
  return os << perm.permission1 << perm.permission1 << perm.permission3;
}// ostreamop
std::istream& operator>>(std::istream& is, const Permissions& perm)
{
    char* perm1 = new char [80];
    sprintf(perm1, "%d", perm.permission1);
    char* perm2 = new char [80];
    sprintf(perm2, "%d", perm.permission2);
    char* perm3 = new char [80];
    sprintf(perm3, "%d", perm.permission3);
    is >> perm1 >> perm2 >> perm3;
    return is;
}// instreamop

void Permissions::set(int originalPermissions, int umask)
{
  totalPermissions = originalPermissions & ~umask;
  int decimal = totalPermissions;
  int rem, count1 = 0, sum = 0;
  
  while (decimal != 0)
  {
    rem = decimal % 8;
    sum = sum + rem * pow(10, count1);
    decimal = decimal / 8;
    count1++;
  }// while
  
  totalPermissions = sum;
  int totalPermissions2 = totalPermissions;
  int count = 0;
  
  while (totalPermissions2 >= 1)// while
  {
      totalPermissions2 /= 10;
      count++;
  }// while
  
  if (totalPermissions == 0)
    count = 3;
  
  setHelper(originalPermissions, umask, count);
  
}  // set())

void Permissions::setHelper(int originalPermissions, int umask, int count)
{
 
  if (count == 3)// if
  {
    permission3 = totalPermissions % 10;
    totalPermissions /= 10;
    permission2 = totalPermissions % 10;
    totalPermissions /= 10;
    permission1 = totalPermissions;
  }// if
  
  if (count == 2)// if
  {
    permission1 = 0;
    permission3 = totalPermissions % 10;
    totalPermissions /= 10;
    permission2 = totalPermissions;
  }// if
  
  if (count == 1)// if
  {
    permission1 = 0;
    permission2 = 0;
    permission3 = totalPermissions;
  }// if
  
}// helper

void Permissions::print()
{
  if (permission1 & 4)// if
    cout << "r";
  else  // no read permissions
    cout << "-";
  
  if (permission1 & 2)// if
    cout << "w";
  else  // no write permissions
    cout << "-";
  
  if (permission1 & 1)// if
    cout << "x";
  else  // no execute permissions
    cout << "-";
  
  printHelper();

}// print

void Permissions::printHelper()
{
  if (permission2 & 4)// if
  cout << "r";
  else  // no read permissions
    cout << "-";
  
  if (permission2 & 2)// if
    cout << "w";
  else  // no write permissions
    cout << "-";
  
  if (permission2 & 1)// if
    cout << "x";
  else  // no execute permissions
    cout << "-";
  
  if (permission3 & 4)// if
    cout << "r";
  else  // no read permissions
    cout << "-";
  
  if (permission3 & 2)// if
    cout << "w";
  else  // no write permissions
    cout << "-";
  
  if (permission3 & 1)// if
    cout << "x";
  else  // no execute permissions
    cout << "-";
    
}  // print()

bool Permissions::isPermitted(int nameBit)
{
    
    switch(nameBit)
    {
        
        case 1:
        {
          if (permission1 & 4)// if
            return true;
          else // else
            return false;
          break;
        }// case
        
        case 2:
        {
          if (permission1 & 2)// if
            return true;
          else // else
            return false;
          break;
        }// case
        
        case 3:
        {
          if (permission1 & 1)// if
            return true;
          else // else
            return false;
          break;
        }// case
        
    }// case
    
    return false;
}// bool