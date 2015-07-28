#ifndef SVECTOR_H
#define	SVECTOR_H

#include <vector>
#include <map>

using namespace std;

template <typename T> 
class SVector
{
  typedef map<string, int> indices;
public:
  int size;
  int excess;
  T data;
  vector<T> list;
  indices indiceMap;
  SVector(int size);
  void push_back(const string &s, const T& data);
  void pop_back();
  const T& operator[](const string& indexstr) const;
}; // class SVector

class Whoops
{
public:
  const string what_arg;
  Whoops(const string& what_ar);
  const char* what() const;
}; // class Whoops

#include "SVector.cpp"
#endif
