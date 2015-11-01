#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    std::ifstream infile;
    string str;
    infile.open("news.txt", ifstream::in);

    if(!infile) {
        cerr<< "error: uable to open input file:" << infile << endl;
    }

    str = infile.getline();
    cout << str << endl;

    return 0;
}

