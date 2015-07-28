#ifndef LIST_H
#define	LIST_H

template <typename T> class List;

template <typename T>
class ListNode
{
public:
  T *data;
  ListNode<T> *next;
  ListNode(T *dat, ListNode *nex);
  ~ListNode();
  friend class List<T>;
};  // class ListNode

template <typename T>
class List
{
  ListNode<T> *head;
public:
  List();
  List(const List &rhs);
  ~List();
  T* operator[] (int index);
  const T* operator[] (int index) const;
  List& operator+= (T *data);
};  // class List

#include "list.cpp"
#endif	// LIST_H 

