// linkedlist.cpp

#include "linkedlist.h"

LinkedList::LinkedList(){
  Node* head = new Node(-1, 0);
  Node* tail = new Node(-1, 0);
  head->next = tail;
  tail->prev = head;
}