#include <iostream>
#include <cstdlib>
#include "List.h"
using namespace std;

int main(int argv, char* argc[]){
    List list;
    list.prints();

//    Node n1, n2;
//    n1.x = 100.0;
//    n1.y = 200.0;
//    n1.z = 300.0;
//    n1.next = NULL;
//
//    n2.x = 100.0;
//    n2.y = 200.0;
//    n2.z = 300.0;
//    n2.next = NULL;

    for(int i = 0; i < 10; i++) {
        Node* tmpNode = (Node*)malloc(sizeof(Node));
        tmpNode->x = i*100;
        tmpNode->y = i*100 + 100;
        tmpNode->z = i*100 + 200;
        list.append(tmpNode);
    }

//    list.append(&n1);
//   list.append(&n2);
    list.prints();
    return 0;
}
