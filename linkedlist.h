// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

class LinkedList
{
private:
  Node *head;
  Node *tail;
  int size;
  void add_between_nodes(Node *new_node, Node *left, Node *right);
  void cut_node(Node *curr_node);

public:
  LinkedList();
  ~LinkedList();
  void push_back(Node *new_node);
  Node *get_front();
  void move_to_back(Node *new_node);
  void pop_front();
  void delete_node(Node *curr_node);
  void print();
};

#endif