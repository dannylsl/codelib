#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;

bool isprime(int num) {
    int i;
    int len = (int)sqrt(num);
    for(i = 2; i <= len; i++) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<int> primeList;
    int n;

    std::cout<<"Please Enter the count number:"<<std::endl;
    std::cin>>n;
    if(n <= 2) {
        std::cout<< "2" << std::endl;
        return 0;
    }
    primeList.push_back(2);

    for(int i = 3; i < n; i++) {
        if(isprime(i) == true) {
            primeList.push_back(i);
        }
    }

    for(vector<int>::size_type i = 0; i != primeList.size(); ++i) {
        std::cout<<std::setw(5) <<primeList[i];
    }
    std::cout<<std::endl;
    return 0;
}
