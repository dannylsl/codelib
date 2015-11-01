#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Node{
    int value;
    char str[10];
};



void set_pos(int *ar, int ar_size, int ele_index, int ele_value, struct Node *ndar) {
    int index = ele_value;
    int i;
    while(ar[index] != -1) {
        index++;
        if(ar[index] == -1) {
            ar[index] = ele_index;
            break;
        }
        if(ar[index] != -1) {
            if(ele_value < ndar[ar[index]].value) {
                for(i = ar_size - 2; i >= index; i--) {
                    ar[i+1] = ar[i];
                }
                ar[index] = -1;
            }
        }
    }
    ar[index] = ele_index;
}

void init_ar(int ar_size, int *ar, int init_value) {
    int i;
    for(i = 0; i < ar_size; i++) {
        ar[i] = init_value;
    }
}

void print_ar(int ar_size, int *ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int i;
    struct Node nd[n];
    int pos[n];

    init_ar(n, pos, -1);

    for(i = 0; i < n ; i++) {
        scanf("%d %s", &nd[i].value, nd[i].str);
        if(i < n/2) {
            memset(nd[i].str, '\0', 10);
            nd[i].str[0] = '-';
        }
    }

    for(i = 0; i < n; i++) {
        set_pos(pos, n, i, nd[i].value, nd);
//        printf("index[%d] %d\n", i, nd[i].value);
//        print_ar(n, pos);
    }


    for(i = 0; i < n; i++) {
        printf("%s ", nd[pos[i]].str);
    }
    printf("\n");

    return 0;
}
