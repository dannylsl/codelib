#include <iostream>
using namespace std;

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        cout<<ar[i]<<" ";
    }
    cout<<endl;
}

int get_sum(int ar_size, int *ar) {
    int i,sum = 0;
    for(i = 0; i < ar_size; i++) {
        sum += ar[i];
    }
    return sum;
}

int find_equal_index(int ar_size, int *ar) {
    int ar_index;
    int suml = 0,sumr = 0;
    if(ar_size == 1) {
        cout<<"YES"<<endl;
        return 1;
    }

    int sum = get_sum(ar_size, ar);

    for(ar_index = 1; ar_index < ar_size - 1 ; ar_index++) {
        suml += ar[ar_index-1];
        sumr = sum - suml - ar[ar_index];
        if(suml == sumr) {
            cout<<"YES"<<endl;
            return 1;
        }
    }
    cout<<"NO"<<endl;
    return 0;
}

int main(int argc, char *argv[]) {
    int T;
    cin>>T;
    int N[T], i, j;
    int *Array[T];

    for(i = 0;i < T; i++) {
        cin>>N[i];
        Array[i] = new int[N[i]];
        for(j = 0; j < N[i]; j++)
            cin>>Array[i][j];
    }

/*
    print_ar(T,N);
    for(i = 0; i < T; i++)
        print_ar(N[i], Array[i]);
*/

    for(i = 0; i < T; i++) {
        find_equal_index(N[i], Array[i]);
        delete [] Array[i];
    }
    return 0;
}
