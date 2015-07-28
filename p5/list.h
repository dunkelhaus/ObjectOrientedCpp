#ifndef LIST_H
#define	LIST_H

#include <iostream>
using namespace std;

class Directory;

class ListNode
{
  friend class List;
  Directory* data;
  ListNode *next;
  ListNode(const Directory *directory, ListNode *n);
  ~ListNode();
}; //ListNode

class List
{
  ListNode *head;
public:
  List();
  List(const List &rhs);
  Directory* operator[](int number) const;
  Directory*& operator[](int element);
  List& operator+=(const Directory *data);
}; //List

#endif