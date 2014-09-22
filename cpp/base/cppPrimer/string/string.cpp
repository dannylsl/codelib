#include <iostream>
#include <string>
using namespace::std;
//using std::cin;
//using std::cout;
//using std::endl;
//using std::string;

int main(int argc, char* argv[]) {

    string word;

    while(cin>>word) {
        cout<< word << endl;
    }

    cout<< "String size:" << word.size() << endl;
    cout<< "String Length:" << word.length() << endl;
    cout<< "Is String empty:" << word.empty() << endl;
    cout<< "String Capacity:" << word.capacity() <<endl;
    word.reserve(100);
    cout<< "String Reverse Capacity:" << word.capacity() <<endl;
    cout<<"INPUT END"<<endl;
    return 0;
}
