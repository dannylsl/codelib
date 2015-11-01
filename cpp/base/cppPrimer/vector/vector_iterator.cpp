#include <iostream>
#include <vector>
using namespace std;

void print_vect(vector<int> vect) {
    for(vector<int>::const_iterator iter = vect.begin(); iter != vect.end();
            iter++) {
        cout<<*iter<<'\t';
    }
}

int main(int argc, char*argv[]) {
    vector<int> vect;
    for(vector<int>::size_type i = 0; i < 10; i++) {
        vect.push_back(i);
        cout<<vect[i]<< '\t';
    }

    cout<< endl << "Output string with iterator:" << endl;
    for(vector<int>::iterator iter = vect.begin(); iter != vect.end();
            iter++) {
        cout<<*iter<<'\t';
    }

    cout<< endl << "Print vector with print_vect() const_iterator :" << endl;
    print_vect(vect);

    cout<<"vector iterator mid (vi.begin() +  vi.end()) / 2 :";
    //vector<int>::iterator mid = (vect.begin() + vect.end()) / 2;
    vector<int>::iterator mid = vect.begin() + vect.size() / 2;
    cout << *mid;
    cout<< endl;
    return 0;
}
