#include <iostream>
using namespace std;

int calc_height(int n) {
    int height = 1;
    int i,cycle_flag = 1;

    for(i = 0; i < n; i++ ) {
        if(cycle_flag == 1) {
            height = 2 * height ;
            cycle_flag = 2;
        }else if(cycle_flag == 2) {
            height = height + 1;
            cycle_flag = 1;
        }
    }
    return height;
}

int main(int argc, char* argv[]) {
    int T,N;
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin>>N;
        cout<<calc_height(N)<<endl;
    }
    return 0;
}
