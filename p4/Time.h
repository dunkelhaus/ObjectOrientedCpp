#ifndef TIME_H
#define	TIME_H
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;



class Time
{
public:
  friend std::ostream& operator<<(std::ostream& os, const Time& tim);
  friend std::istream& operator>>(std::istream& os, const Time& tim);
  struct tm modificationTime;
  char* tim;
  Time();
  struct tm update();
  void set();
  void print();
}; // Time

#endif	// TIME_H 

