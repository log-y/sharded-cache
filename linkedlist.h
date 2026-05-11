// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

class LinkedList {
  private:
    Node* head;
    Node* tail;
    int size;

    void add_between_nodes(Node* new_node, Node* left, Node* right);

  public:
    LinkedList();
    void push_back(Node* new_node);
    Node* get_back();
    void push_front(Node* new_node);
    Node* get_front();
};

#endif 