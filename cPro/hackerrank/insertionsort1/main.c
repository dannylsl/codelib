//https://www.hackerrank.com/challenges/insertionsort1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void print_ar(int ar_size, int *ar) {
	int i;
	for(i = 0; i < ar_size; i++) {
		printf("%d ",ar[i]);
	}
	printf("\n");
}

void insertionSort(int ar_size, int *  ar) {
	int value =  ar[ar_size-1],i;

	for(i = 2; i <= ar_size; i++) {
		if(ar[ar_size-i] > value ) {
			ar[ar_size-i+1] = ar[ar_size-i];	
			print_ar(ar_size, ar);
		}else {
			ar[ar_size-i+1] = value;		
			print_ar(ar_size, ar);
			break;
		}	
		if(i == ar_size && ar[0] > value) {
			ar[0] = value;
			print_ar(ar_size, ar);
		}
	}
}

int main(void) {

	int _ar_size;
	scanf("%d", &_ar_size);
	int _ar[_ar_size], _ar_i;
	for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
		scanf("%d", &_ar[_ar_i]); 
	}
	insertionSort(_ar_size, _ar);
	return 0;
}

