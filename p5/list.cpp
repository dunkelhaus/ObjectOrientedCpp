#include <cstring>
#include <iostream>
#include "list.h"
#include "directory.h"
using namespace std;

List::List() : head(NULL)
{
  
} // List()

List::List(const List &rhs)
{
  ListNode *ptr, *prev;
  
  if (!rhs.head)
    return;
  
  head = new ListNode (rhs.head->data, NULL);
  prev = head;
  ptr = rhs.head->next;
  
  while (ptr!=NULL)
  {
    prev->next = new ListNode(ptr->data, NULL);
    prev = prev->next;
    ptr = ptr->next;
    
  } // while ptr exists
    
} // copy List()

ListNode::ListNode(const Directory *directory, ListNode *n): next(n)
{
  data = new Directory(*directory);
} //ListNode

ListNode::~ListNode()
{
  delete data;
} //~ListNode

Directory* List::operator[](int number) const
{
  ListNode *ptr;
  ptr = head;
  
  if (number == 0)
    return (head)->data;
  else //not 0
    
  for (int i = 0; i != number; i++)
    ptr = ptr->next;
  
  return ptr->data;
  
} //operator[]

Directory*& List::operator[](int number)
{
  ListNode *ptr;
  ptr = head;
  
  if (number == 0)
    return head->data;
  else //not 0
    
  for (int i = 0; i != number; i++)
    ptr = ptr->next;
  
  return ptr->data;
} //operator[]

List& List::operator+=(const Directory *data)
{
  ListNode *ptr, *prev = NULL;
  
  for (ptr = head; ptr && *(ptr->data) < *data; ptr = ptr->next)
    prev = ptr;
  
  if (!prev)
    head = new ListNode(data, head);
  
  else
    prev->next = new ListNode(data, ptr);
  
  return *this;
} // +=