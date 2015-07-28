#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <cassert>
#include <exception>
#include <new>
// #include "SVector.h"

using namespace std;

template <typename T>
SVector<T>::SVector(int siz)
{
  size = siz;
  excess = 0;

  if (size < 0) // if
    throw (bad_alloc());
} // constructor

template <typename T>
void SVector<T>::push_back(const string& s, const T& data)
{
  assert(indiceMap.find(s) == indiceMap.end());
  
  if (indiceMap.find(s) != indiceMap.end()) // if
    throw (Whoops(s));
      
  
  list.push_back(data);
  int siz = indiceMap.size();
  pair<string, int> set;
  set.first = s;
  set.second = siz;
  indiceMap.insert(set);
} // push back()

template <typename T>
void SVector<T>::pop_back()
{
  string message = "";

  if (excess > 0)
    excess--;

  message = "Underflow error";
  excess = size - list.size();
  assert(!list.empty());
  
  if (list.empty() && excess <= 0) // if
    throw (underflow_error(message));
  
  if (excess > 0 && list.empty())
    return;

  map<string, int>::iterator itr;
  map<string, int>::iterator i;
  
  for (itr = indiceMap.begin(); itr != indiceMap.end(); itr++)
    i = itr;

  // int size = list.size();
  list.pop_back();
  indiceMap.erase(i);
  size--;
} // pop back

template <typename T>
const T& SVector<T>::operator[](const string& indexstr) const
{
  // int flag = 0;
  string message = "";
  message = "Range error: ";
  message += indexstr;
  map<string, int>::const_iterator itr = indiceMap.find(indexstr);
  assert(itr != indiceMap.end());
  
  if (itr == indiceMap.end()) // if
    throw (range_error(message));
  
  int index = indiceMap.at(indexstr);
  return list.at(index);
  // return val;
} // operator[]

Whoops::Whoops(const string& what_ar) : what_arg(what_ar.c_str())
{
} // constructor

const char* Whoops::what() const
{
  string message = "";
  string message2 = "";
  message2 = string(what_arg);
  message = "Duplicated index: ";
  message += message2;
  return message.c_str();
} // what()
