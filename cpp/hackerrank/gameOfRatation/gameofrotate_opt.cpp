/**
 * Common solution as gameofrotate.cpp return timeout while deal with big data
 * With Mathematical derivation with the Formula
 * Array A with N element
 *      Delta(k) = PMEAN(k+1) - PMEAN[k] = Sum(A) - N * A[N-k-1]
 * As for PMEAN(k)      0 <= k <= N-1
 * As for PMEAN(k+1)    0 <= k+1 <= N-1
 * We can judge when 0 <= k <= k-2  Delta(k) works
 *  PMEAN(k+1) = PMEAN(k) + Delta(k) = PMEAN(k) + Sum(A) - N * A[N-k-1]
 **/

#include <iostream>
using namespace std;

long long get_ar_sum(int ar_size, long long *ar) {
    int i;
    long long sum = 0;

    for( i = 0; i < ar_size; i++) {
        sum += ar[i];
    }

    return sum;
}

long long calc_PMEAN_0(int ar_size,  long long *ar) {
    long long sum = 0;
    for(int i = 0; i < ar_size; i++) {
        sum += ar[i] * (i+1);
    }
    return sum;
}


int main(int argc, char * argv[]) {
    int N,i;
    cin>>N;
    long long PMEAN[N];
    long long A[N];
    long long max = 0, sum = 0;
    for(i = 0; i < N; i++) {
        cin>>A[i];
    }

    sum = get_ar_sum(N, A);
    PMEAN[0] = calc_PMEAN_0(N, A);
    max = PMEAN[0];

    for(i = 0; i < N - 1; i++) {
        PMEAN[i+1] = PMEAN[i] + sum - N * A[N-i-1];
        if(PMEAN[i+1] > max)
            max = PMEAN[i+1];
    }

    cout<<max<<endl;
    return 0;
}
