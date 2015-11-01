#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;


int getIntegerComplement(int n) {
    int in = n;
    int highest = 1;
    int inverse = 0;
    int int_bit = sizeof(int) * 8;

    while(1) {
        in = in >> 1;
        if(in != 0) {
            highest ++;
        }else{
            break;
        }
    }

    inverse = ~n;
    inverse = inverse<<(int_bit - highest);
    inverse = inverse>>(int_bit - highest);
    return inverse;
}

int main() {
    int res;
    int _n;
    cin >> _n;

    res = getIntegerComplement(_n);
    cout << res;

    return 0;
}
