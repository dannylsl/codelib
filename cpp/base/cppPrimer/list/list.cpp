#include <iostream>
#include <iomanip>
#include <list>

using namespace std;

int main(int argc, char* argv[]) {
    list<int> link;
    int value;
    cout<< "Input 10 numbers" << endl;
    for(int i = 0; i < 10; i++) {
        cin>>value;
        link.push_back(value);
    }

    list<int>::iterator p = link.begin();
    for(; p != link.end(); p++) {
        cout<<setw(5)<<*p;
    }
    cout<<endl;

    cout<< "Enter a value to remove from the link" << endl;
    cin>> value;
    link.remove(value);
    cout<<"Link List:" << endl;
    for(list<int>::iterator iter = link.begin(); iter != link.end(); iter++)
        cout<< setw(5)<<*iter;
    cout <<endl;

    return 0;
}
