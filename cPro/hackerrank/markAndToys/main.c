//https://www.hackerrank.com/challenges/mark-and-toys


#include <stdio.h>
#include <malloc.h>

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    }
}

void insertionSort(int ar_size, int *  ar) {
    int i,j, available;
    for(i = 0; i < ar_size; i++) {
        int value = ar[i];
        available = i;
        for(j=i-1; j >= 0; j--) {
            if(value < ar[j]) {
                ar[available] = ar[j];
                available = j;
            }else{
                break;
            }
        }
        ar[available] = value;
    }
}

int get_max_buy( int ar_size, int * ar, int money) {
    int i;
    int sum = 0;
    int max_count = 0;

    for(i = 0; i < ar_size; i++) {
        if( money > sum + ar[i]) {
            sum = sum + ar[i];
            max_count++;
        }else {
            break;
        }
    }
    return max_count;
}

int main(int argc, char* argv[]) {
    int N, K, i, j;
    int *toys;
    int tmp, count;
    scanf("%d %d", &N, &K);
    toys = (int*)malloc(sizeof(int)*N);

    for(i = 0, j =0; i < N; i++) {
        scanf("%d", &tmp);
        if(tmp < K){
            toys[j] = tmp;
            j++;
        }
    }

    insertionSort(j, toys);
    count = get_max_buy(j, toys, K);
    printf("%d",count);
    return 0;
}

