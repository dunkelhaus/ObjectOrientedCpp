#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include <exception>

#include "SVector.h"

using namespace std;

int main(int argCount, const char *arguments[])
{
  char code;
  string strindex;
  int size;
  int value;

  try 
  {
    ifstream in(arguments[1]);
    char c;
    int i = 0;
  
    while (in.get(c))
      if (c == '\n') // if
          ++i;
  
    in.close();
    i--;
    ifstream inf(arguments[1]);
    inf >> size;
    SVector<int> strvector(size);
    inf.ignore(10, '\n');
    char* line = new char[100];
  
    for (int j = 0; j != i; j++)
    {
      inf.getline(line, 300);
      code = line[0];
      string val;
      int k = 0;
      int length = strlen(line);
  
      for (int i = 0; i < length; i++)
      {
        if (isdigit(line[i])) // if
          val += line[i];
  
        if (isalpha(line[i]) && i != 0) // if
        {
          k = i;
          break;
        } // if
      } // if
  
      strindex = string(line);
      strindex = strindex.substr(k);
      value = atoi(val.c_str());

      switch (code)
      {

        case 'A':

          try
          {
            int accessvalue = strvector[strindex];
            cout << "Access value: " << accessvalue << endl;
          } // try

          catch(range_error &e)
          {
            cout << e.what();
            cout << endl; 
          } // catch

          break;

        case 'U':
          
          try
          {
            strvector.push_back(strindex, value);
          } // try

          catch(Whoops &e)
          {
            cout << e.what();
            cout << endl;
          } // catch

          break;

        case 'O':

          try
          {
            strvector.pop_back();
          } // try

          catch(underflow_error &e)
          {
            cout << e.what();
            cout << endl;
          } // catch

          break;
      } // switch

    }  // loop

  } // try

  catch (bad_alloc &e)
  {
    cout << e.what();
  } // catch

} // int main
