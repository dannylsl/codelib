#include <stdio.h>
#include <malloc.h>

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    }
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int ar_size, int *ar) {
    int pivot = ar[ar_size - 1];
    int l_len = 0, i;

    for(i = 0; i < ar_size; i++) {
        if(ar[i] <= pivot) {
            swap(&ar[i], &ar[l_len]);
            if(i != ar_size -1)
                l_len++;
        }
    }

    if(l_len > 1) {
        quickSort(l_len, ar);
    }
    if(ar_size - l_len - 1 > 1) {
        quickSort(ar_size - l_len - 1, ar+l_len+1);
    }
}

int sum_ar(int ar_size, int *ar) {
    int i,sum = 0;

    for(i = 0; i < ar_size; i++) {
        sum = sum + ar[i];
    }
    return sum;
}

int is_K_exist(int N, int *A, int *B, int K) {
    int i,j;
    quickSort(N, A);
    quickSort(N, B);
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(B[j] != -1) {
                if(A[i] + B[j] >= K) {
                    B[j] = -1;
                    break;
                }
            }
        }
    }
    //printf("N=%d, sum_ar=%d\n",N, sum_ar(N,B));
    if( sum_ar(N, B) == -1*N) {
        return 1;
    }else{
        return 0;
    }
}

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);
    int N[T],K[T];
    int *A[T], *B[T];
    int *tmp;
    int i,j;
    for(i = 0; i < T; i++) {
        scanf("%d %d", &N[i], &K[i]);
        tmp = (int*)malloc(sizeof(int) * N[i]);
        for(j = 0; j < N[i]; j++)
            scanf("%d", &tmp[j]);
        A[i] = tmp;

        tmp = (int*)malloc(sizeof(int) * N[i]);
        for(j = 0; j < N[i]; j++)
            scanf("%d", &tmp[j]);
        B[i] = tmp;
    }

    for(i = 0; i < T; i++) {
        if(1 == is_K_exist(N[i], A[i], B[i], K[i])) {
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }

    return 0;
}
