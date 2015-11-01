#include <iostream>
#include <malloc.h>
using namespace std;

struct Node {
    int value;
    struct Node *next;
};

int is_x_work(int x, int ar_size, int *ar, int sum) {
    int i ;
    int volumn = x;
    if(sum % x != 0)
        return 0;
    for(i = 0; i < ar_size; i++) {
        volumn = volumn - ar[i];
        if(volumn > 0) {
            continue;
        } else if(volumn < 0) {
            return 0;
        } else {
            volumn = x;
            continue;
        }
    }
    return (volumn == x) ? x : 0;
}

int main(int argc, char *argv[]) {
//    int max = 0;
    int sum = 0, i;
    int n, k;
    cin>>n;
    int A[n];
    struct Node *head;
    struct Node *foot;
    struct Node *nd;
    int node_len = 0;

    for(i = 0; i < n; i++) {
        cin>>A[i];
        sum += A[i];
    }

    for(i = 0,k = 0; i < n; i++) {
        k += A[i];
        if( is_x_work(k, n, A, sum) != 0 ) {
            nd = (struct Node*)malloc(sizeof(struct Node));
            nd->value = k;
            if(node_len == 0) {
                head = nd;
                foot = head;
            } else {
                foot->next = nd;
                foot = nd;
            }
            node_len++;
        };
        if( k > sum)
            break;
    }

    nd = head;
    while(node_len--) {
        cout<<nd->value<< " ";
        nd = nd->next;
    }
    return 0;
}
