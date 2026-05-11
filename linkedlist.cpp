// linkedlist.cpp

#include "linkedlist.h"

LinkedList::LinkedList()
{
  Node *head = new Node(-1, 0);
  Node *tail = new Node(-1, 0);
  head->next = tail;
  tail->prev = head;
  size = 0;
}

Node *LinkedList::get_back()
{
  if (size == 0)
  {
    return nullptr;
  }
  return tail->prev;
}

Node *LinkedList::get_front()
{
  if (size == 0)
  {
    return nullptr;
  }
  return head->next;
}

void LinkedList::add_between_nodes(Node *new_node, Node *left, Node *right)
{
  left->next = new_node;
  new_node->prev = left;
  right->prev = new_node;
  new_node->next = right;
}

void LinkedList::push_back(Node *new_node)
{
  if (size == 0)
  {
    add_between_nodes(new_node, head, tail);
  }

  Node *last = tail->prev;

  add_between_nodes(new_node, last, tail);
}

void LinkedList::push_front(Node *new_node)
{
  if (size == 0)
  {
    add_between_nodes(new_node, head, tail);
  }

  Node *front = tail->prev;

  add_between_nodes(new_node, head, front);
}