// linkedlist.cpp

#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList()
{
  try 
  {
    Node *head = new Node(-1, 0);
    Node *tail = new Node(-1, 0);
  }
  catch (const std::bad_alloc& e){
    std::cerr << "error allocating" << std::endl;
  }
  
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
  if (new_node == nullptr || left == nullptr || right == nullptr){
    return;
  }
  left->next = new_node;
  new_node->prev = left;
  right->prev = new_node;
  new_node->next = right;
  size++;
}

// connects the 2 nodes around new_node to each other
void LinkedList::cut_node(Node* curr_node){
  if (curr_node == nullptr || curr_node->prev == nullptr || curr_node->next == nullptr) {
    return;
  }
  Node* next_node = curr_node->next;
  Node* prev_node = curr_node->prev;
  prev_node->next = next_node;
  next_node->prev = prev_node;
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

void LinkedList::move_to_back(Node* new_node){
  cut_node(new_node);
  push_back(new_node);
}

void LinkedList::pop_front(){
  if (size == 0){
    return;
  }
  Node* first = head->next;
  cut_node(first);
  delete first;
  size--;
}

int LinkedList::get_size(){
  return size;
}

LinkedList::~LinkedList(){
  Node* curr_node = head;
  while (curr_node != nullptr){
    Node* next = curr_node->next;
    delete curr_node;
    curr_node = next;
  }
}