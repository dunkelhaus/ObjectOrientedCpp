// Author: Sean Davis

#include <iostream>

template <typename T>
ListNode<T>::ListNode(T *dat, ListNode *nex) : data(dat),
  next(nex)
{
}   // ListNode()

template <typename T>
ListNode<T>::~ListNode()
{
  delete data;
}  // ~ListNode()

template <typename T>
List<T>::List() : head(NULL)
{
} // List()

template <typename T>
List<T>::List(const List &rhs)
{
  ListNode<T> *rhsPtr, *prev = NULL;
  
  for (rhsPtr = rhs.head; rhsPtr; rhsPtr = rhsPtr->next)
  {
    T *data = new T(*rhsPtr->data);
    
    if (!prev)
      prev = head = new ListNode<T>(data, NULL);
    else  // inserting after first node
      prev = prev->next = new ListNode<T>(data, NULL);
  }  // for each node in list
}  // List copy constructor

template <typename T>
List<T>::~List() 
{
  for (ListNode<T> *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }  // for each node in the list
} // ~List()

template <typename T>
T* List<T>::operator[] (int index)
{
  ListNode<T> *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
    
  if (ptr)
    return ptr->data;
  else  // ptr is NULL so index is beyond the end of the list
    return NULL;
}   // operator[]

template <typename T>
const T* List<T>::operator[] (int index) const
{
  ListNode<T> *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
    
  if (ptr)
    return ptr->data;
  else  // ptr is NULL so index is beyond the end of the list
    return NULL;
}   // operator[] const]

template <typename T>
 List<T>& List<T>::operator+= (T *data)
 {
   ListNode<T> *ptr, *prev = NULL;
   
   for (ptr = head; ptr && *ptr->data < *data; ptr = ptr->next)
     prev = ptr;
   
    if (!prev)
     head = new ListNode<T>(data, head);
   else  // if inserting in middle of list.
     prev->next = new ListNode<T>(data, ptr);

   return *this;
 }  // operator+=
 
 
  
