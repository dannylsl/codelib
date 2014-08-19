#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    }
}
void partition(int ar_size, int *  ar) {
    int l_ar[ar_size], r_ar[ar_size];
    int l_ar_len = 0, r_ar_len = 0;
    int value = ar[0];
    int i;
    for(i = 1; i < ar_size; i++) {
        if( ar[i] <= value ) {
            l_ar[l_ar_len] = ar[i];
            l_ar_len++;
        }else if(ar[i] > value) {
            r_ar[r_ar_len] = ar[i];
            r_ar_len++;
        }
    }
    // Combine Array
    for(i = 0; i < ar_size; i++) {
        if( i < l_ar_len) {
            ar[i] = l_ar[i];
        }else if(i == l_ar_len) {
            ar[i] = value;
        }else {
            ar[i] = r_ar[i - l_ar_len - 1];
        }
    }
    print_ar(ar_size, ar);
}

int main(void) {

    int _ar_size;
    scanf("%d", &_ar_size);
    int _ar[_ar_size], _ar_i;
    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) {
        scanf("%d", &_ar[_ar_i]);
    }

    partition(_ar_size, _ar);

    return 0;
}

