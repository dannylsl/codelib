#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node {
    int ele_pos;
    struct Node *next;
}Node;

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int i,j;
    int num[n];
    char str[n][10];

    Node *ndlist[101];
    Node *ndlist_foot[101];
    int nd_len[101] = {0};
    Node *node;

    printf("Start");

    for(i = 0; i < n ; i++) {
        scanf("%d %s", &num[i], str[i]);
        if(i < n/2) {
            memset(str[i], '\0', 10);
            str[i][0] = '-';
        }
    }

    for(i = 0; i < n; i++) {
        node = (Node*)malloc(sizeof(Node));
        node->ele_pos = i;

        if(nd_len[num[i]] == 0) {
            ndlist[num[i]] = node;
            ndlist_foot[num[i]] = node;
        }else {
            ndlist_foot[num[i]]->next = node;
            ndlist_foot[num[i]] = node;
        }

        nd_len[num[i]]++;
    }

    for(i = 0; i < 101; i++) {
        node = ndlist[i];
        for(j = 0; j < nd_len[i]; j++) {
            printf("%s ",str[node->ele_pos]);
            node = node->next;
        }
    }

    return 0;
}
