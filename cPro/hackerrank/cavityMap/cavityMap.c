//https://www.hackerrank.com/challenges/cavity-map

#include <stdio.h>
#include <malloc.h>

void print_map(int n, char **map) {
    int i,j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    return;
}

void copy_map(int n, char **dest, char **src) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dest[i][j] = src[i][j];
    return;
}

int is_cavity(int pos_x, int pos_y, char **map, char **tmp) {
    int i,j;
    i = pos_x;
    j = pos_y;
    int value = map[pos_x][pos_y];
    if(tmp[i-1][j] >= value)
        return 0;
    if(tmp[i][j-1] >= value)
        return 0;
    if(tmp[i][j+1] >= value)
        return 0;
    if(tmp[i+1][j] >= value)
        return 0;
    map[pos_x][pos_y] = 'X';
    return 1;
};

void find_cavity(int n, char **map, char**tmp) {
    int i, j;
    for(i = 1; i < n - 1; i++) {
        for(j = 1; j < n - 1; j++) {
            is_cavity(i, j, map, tmp);
        }
    }
    return;
}

int main(int argc, char* argv[]) {
    int n,i;
    char **map, **tmp;
    scanf("%d",&n);
    map = (char**)malloc(sizeof(char*) * n);
    tmp = (char**)malloc(sizeof(char*) * n);
    for(i = 0; i < n; i++) {
        map[i] = (char*)malloc(sizeof(char) * n);
        tmp[i] = (char*)malloc(sizeof(char) * n);
        scanf("%s", map[i]);
    }
    copy_map(n, tmp, map);
    find_cavity(n, map, tmp);

    print_map(n, map);
    return 0;
}

