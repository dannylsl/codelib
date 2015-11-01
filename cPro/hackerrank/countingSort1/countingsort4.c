#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node {
    char str[10];
    struct Node *next;
}Node;

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int i,j, num, max;
    char str[10];

    Node *ndlist[100];
    Node *ndlist_foot[100];
    int nd_len[100] = {0};
    Node *node;

    max = 0;
    for(i = 0; i < n ; i++) {
        scanf("%d %s", &num, str);
        if(max < num)
            max = num;
        if(i < n/2) {
            memset(str, '\0', 10);
            str[0] = '-';
        }

        node = (Node*)malloc(sizeof(Node));
        strcpy(node->str, str);

        if(nd_len[num] == 0) {
            ndlist[num] = node;
            ndlist_foot[num] = node;
        }else {
            ndlist_foot[num]->next = node;
            ndlist_foot[num] = node;
        }

        nd_len[num]++;
    }

    for(i = 0; i <= max; i++) {
        node = ndlist[i];
        for(j = 0; j < nd_len[i]; j++) {
            printf("%s ",node->str);
            node = node->next;
        }
    }

    return 0;
}
