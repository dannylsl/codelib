#include "List.h"

void List::append(Node* node){
    if( NULL == this->head ) {
        this->head = node;
        this->foot = node;
    }else {
        this->foot->next = node;
        this->foot = this->foot->next;
    }

    return;
}

void List::prints() {
    Node* cur = this->head;
    cout<<"List Content"<<endl;
    while( NULL != cur ) {
        cout<<"[NODE] x="<<cur->x<<" y="<<cur->y<<" z="<<cur->z<<endl;
        cur = cur->next;
    }
    cout<<"END"<<endl;
}
