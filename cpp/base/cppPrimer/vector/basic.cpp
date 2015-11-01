#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    vector<string> svec(10, "null");
    string s;
    vector<int>::size_type i;
    for( i = 0; i < svec.size(); i++) {
        cout<< i << " " << svec[i] << endl;
    }
    cout << "Input a new String:" <<endl;
    cin >> s;
    svec.push_back(s);
    cout<< i << " " << svec[i] << endl;

    /*
        cout << "Insert data with svec[11]" << endl;
        svec[11] = "aaaa";  //Crashed Here
        cout << svec[11] << endl;
    */
}
