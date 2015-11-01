#include <iostream>
using namespace std;

class A {
public:
    A(int a);
    void print() {cout<<"Hello World"<<endl;}
private:
    int a;
};

inline A::A(int a){
    this->a = a;
    cout<<this->a<<endl;
}

int main(int argc, char* argv[]) {
    A* a = new A(1);
    A* tmp = NULL;
    tmp->print();
    return 0;
}

