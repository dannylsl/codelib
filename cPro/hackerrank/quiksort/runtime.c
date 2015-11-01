#include <stdio.h>

int swap_count = 0;
int shift_count= 0;

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    }
}

int insertionSort(int ar_size, int *  ar) {
    int i,j, available;
    int count = 0;
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

int main(int argc, char* argv[]) {
    int _ar_size, i;
    scanf("%d", &_ar_size);
    int ar[_ar_size], ar2[_ar_size];

    for(i = 0; i < _ar_size; i++) {
        scanf("%d", &ar[i]);
        ar2[i] = ar[i];
    }

    quickSort(_ar_size, ar);
    shift_count = insertionSort(_ar_size, ar2);

    printf("%d", shift_count - swap_count);
    //print_ar(_ar_size, ar);
    //printf("\n[%d]\n", swap_count);
    return 0;
}


