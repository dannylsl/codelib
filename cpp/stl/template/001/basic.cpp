#include <iostream>
using namespace std;

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

template <typename T>
inline T const& min2( T const& a, T const& b) {
    return a > b ? b : a;
}

int main() {
    cout << "The max value is " << ::max(3,5) << endl;
    cout << "The max value is " << ::max(3.3,5.6) << endl;
    // Since max() has the same function name with function in C++ library
    // Here we must use '::' to set the reference to current file rather than C++ library

    // if the function is unique, the '::' is not must 
    cout << "The min value is " << min2(4.4,3.3) << endl;
    cout << "The min value is " << ::min2(5 , 8) << endl;

    return 0;
}
