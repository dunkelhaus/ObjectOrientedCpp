// Author: Sean Davis
#include <ctime>
#include <iostream>
#include <iomanip>
#include "Time.h"
using namespace std;

Time::Time() 
{
  update();
} // Time()


 void Time::print() const
 {
   const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
     "Aug", "Sep", "Oct", "Nov", "Dec"};
   
   cout << months[modificationTime.tm_mon] << setw(3) 
     << modificationTime.tm_mday << setw(3) << modificationTime.tm_hour
     << ":"  << setfill('0') << setw(2) << modificationTime.tm_min << ' ' 
     << setfill(' ');
 }  // print()
 
 
 void Time::update()
 {
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    modificationTime = *timeinfo;
 }  // update())

 
 ostream& operator<< (ostream &os, const Time &time)
 {
    os << time.modificationTime.tm_mon << ' ' << time.modificationTime.tm_mday 
       << ' ' << time.modificationTime.tm_hour << ' ' 
       << time.modificationTime.tm_min; 
   return os;
 }  // operator<<
 
 
  istream& operator>> (istream &is, Time &time)
 {
    is >> time.modificationTime.tm_mon >> time.modificationTime.tm_mday 
       >> time.modificationTime.tm_hour >> time.modificationTime.tm_min; 
   return is;
 }  // operator>>
