#ifndef __OBJECT_H
#define __OBJECT_H

#include <iostream>
using namespace std;

struct Node {
    double x;
    double y;
    double z;
    Node* next;
};

class List {
    public:
        List(){head = NULL;};
        void append(Node* node);
        void prints();
    private:
        Node* head;
        Node* foot;
};

#endif
