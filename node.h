// node.h

#ifndef NODE_H
#define NODE_H

class Node{
  public:
    int key;
    int val;
    Node* next;
    Node* prev;
    Node(int k, int v);
};

#endif