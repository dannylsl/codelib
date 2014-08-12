/*
   Give an arrag and value, remove all instances of that value in place and return the new length
   The order of elements cant be changed. It doesn't matter what you leave beyond the new length
https://oj.leetcode.com/problems/remove-element/
 */
#include <iostream>
#include <cstring>
using namespace std;

int removeElement2(int A[], int n, int elem) {
    int num=0,i;
    for(i=0;i<n;++i)
        if(A[i]!=elem)A[num++]=A[i];
    return num;
}

int removeElement(int A[], int n, int elem) {
    int i,j;
    for( i = 0, j = 0; i < n; i++) {
        if(A[i] == elem) {
            continue;
        }else {
            A[i] = elem + 1;
            j++;
        }
    }
    return j;
}

int main(int argc, char *argv[]) {
    int A[] = {1,2,3,3,4,3,5,6,7,8,9,10};

    cout<<removeElement(A, 12, 3)<<endl;
//    cout<<removeElement2(A, 12, 3)<<endl;
    cout<<removeElement(A, 12, 3)<<endl;
    cout<<"hello World"<<endl;
    return 0;
}
