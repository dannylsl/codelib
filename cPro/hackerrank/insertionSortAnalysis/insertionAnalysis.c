#include <stdio.h>
#include <malloc.h>

long shift_count= 0;

int insertionSort(int ar_size, int *  ar) {
    int i,j, available;
    long count = 0;
    for(i = 0; i < ar_size; i++) {
        int value = ar[i];
        available = i;
        for(j=i-1; j >= 0; j--) {
            if(value < ar[j]) {
                ar[available] = ar[j];
                available = j;
                count++;
            }else{
                break;
            }
        }
        ar[available] = value;
    }
    return count;
}

int insertionCount(int ar_size, int *  ar) {
    int i,j;
    int count = 0;
    for(i = 1; i < ar_size; i++) {
        for(j = 0; j < i; j++) {
            if(ar[j] > ar[i])
                count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);

    int _ar_size[T], i,j;
    int *ar[T];

    for(i = 0; i < T; i++) {
        scanf("%d", &_ar_size[i]);

        ar[i] = (int *)malloc(sizeof(int) * _ar_size[i]);

        for(j = 0; j < _ar_size[i]; j++) {
            scanf("%d", &ar[i][j]);
        }
    }

    for(i = 0; i < T; i++) {
        shift_count = insertionSort(_ar_size[i], ar[i]);
//        shift_count = insertionCount(_ar_size[i], ar[i]);
        printf("%ld\n", shift_count );
    }
    return 0;
}
