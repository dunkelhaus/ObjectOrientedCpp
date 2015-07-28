#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include "Time.h"

using namespace std;

Time::Time()
{
    
}// constructor

ostream& operator<<(ostream& os, const Time& tim)
{
  return os << tim.modificationTime.tm_mon << " " 
          << tim.modificationTime.tm_mday << " " << 
          tim.modificationTime.tm_hour << " " << tim.modificationTime.tm_min;
}// stream
istream& operator>>(istream& is, const Time& tim)
{
    char* mon = new char [80];
    sprintf(mon, "%d", tim.modificationTime.tm_mon);
    char* day = new char [80];
    sprintf(day, "%d", tim.modificationTime.tm_mon);
    char* hour = new char [80];
    sprintf(hour, "%d", tim.modificationTime.tm_mon);
    char* min = new char [80];
    sprintf(min, "%d", tim.modificationTime.tm_mon);
    is >> mon;
    is >> day;
    is >> hour;
    is >> min;
    return is;
}// stream

struct tm Time::update()
{
    time_t now = time(0);
    modificationTime = *localtime(&now);
    return modificationTime;
}// update

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
void Time::set()
{
    time_t current = time(0);
    char time1[80];
    modificationTime = *localtime(&current);
    strftime(time1, sizeof(time1), "%b %e %R", &modificationTime);
    tim = new char[80];
    strcpy(tim, time1);
}// set

void Time::print()
{
    cout << tim;
}// time

