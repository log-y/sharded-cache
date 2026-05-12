// linkedlist.cpp

#include "linkedlist.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
  try
  {
    head = new Node(-1, 0);
    tail = new Node(-1, 0);
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
    head->prev = nullptr;
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "error allocating" << std::endl;
  }

  size = 0;
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
  if (new_node == nullptr || left == nullptr || right == nullptr)
  {
    return;
  }

  left->next = new_node;
  new_node->prev = left;
  right->prev = new_node;
  new_node->next = right;
  size++;
}

// connects the 2 nodes around new_node to each other
void LinkedList::cut_node(Node *curr_node)
{
  if (curr_node == nullptr || curr_node->prev == nullptr || curr_node->next == nullptr)
  {
    return;
  }

  Node *prev_node = curr_node->prev;
  Node *next_node = curr_node->next;

  prev_node->next = next_node;
  next_node->prev = prev_node;
 
  curr_node->next = nullptr;
  curr_node->prev = nullptr;
}

void LinkedList::pop_front()
{
  if (size == 0)
  {
    return;
  }
  Node *first = head->next;
  cut_node(first);
  delete first;
  size--;
}

void LinkedList::push_back(Node *new_node)
{
  if (size == 0)
  {
    add_between_nodes(new_node, head, tail);
    return;
  }

  Node *last = tail->prev;

  add_between_nodes(new_node, last, tail);
}

void LinkedList::move_to_back(Node *new_node)
{
  if (size == 0 || size == 1){
    return;
  }
  cut_node(new_node);
  push_back(new_node);
}

void LinkedList::delete_node(Node *curr_node)
{
  cut_node(curr_node);
  delete curr_node;
}

LinkedList::~LinkedList()
{
  Node *curr_node = head;
  while (curr_node != nullptr)
  {
    Node *next = curr_node->next;
    delete curr_node;
    curr_node = next;
  }
}

void LinkedList::print()
{
  Node *curr_node = head;
  while (curr_node != nullptr)
  {
    Node *next = curr_node->next;
    std::cout << curr_node->key << " " << curr_node->val << std::endl;
    curr_node = next;
  }
}