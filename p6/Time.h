#ifndef TIME_H
#define	TIME_H

#include <ctime>
#include <iostream>
using namespace std;


class Time 
{
  struct tm modificationTime;
public:
  Time();
  void print() const;
  void update();
  friend ostream& operator<< (ostream &os, const Time &time);
  friend istream& operator>> (istream &os, Time &time);
};  // class Time

#endif	// TIME_H

