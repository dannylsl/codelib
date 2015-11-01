#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char* argv[]) {
    string strval("1100");
    bitset<32> bitvec(strval);
    cout << bitvec << endl;

    string str("1111111100000001101");
    bitset<32> bitvec2(str, 5, 6);
    cout << bitvec2 << endl;
    bitset<32> bitvec3(str, str.size() - 4);
    cout << bitvec3 << endl;

    for(size_t i = 0; i != bitvec.size(); i++) {
        if(bitvec.test(i)) {
            cout<< "POS " << i << " :" << bitvec[i] << endl;
        }
    }

    return 0;
}
