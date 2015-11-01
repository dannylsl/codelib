#include <iostream>
#include <vector>
#include <string>
using namespace std;
using std::string;

string upper(string str) {
    string::size_type len = str.size();
    for(string::size_type index = 0; index != str.size(); index++) {
        if(isalpha(str[index])) {
            str[index] = (char)toupper(str[index]);
        }
    }
    return str;
}

int main(int argc, char* argv[]) {
    vector<string> words;
    string str;
    cout << "Input your words" << endl;
    cin >> str;
    words.push_back(str);
    cout << "VECTOR STRING:" << words[0] << endl;
    cout << "UPPERED STRING :" << upper(words[0]) << endl;
    return 0;
}
