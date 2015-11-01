#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cell {
    int data;
    struct Cell *next;
}Cell;

Cell *createLink(Cell* head, int data[], int data_len) {
    Cell *tmpCell, *ptr = head;
    int i;
    for(i = 0; i < data_len; i++) {
        tmpCell = (Cell*)malloc(sizeof(Cell)*data_len);
        tmpCell->data = data[i];
        if(i == 0) {
            head = tmpCell;
            ptr = head;
        }else {
            ptr->next = tmpCell;
            ptr = ptr->next;
        }
    }
    ptr->next = NULL;
    return head;
}

void printCellLink(Cell*head) {
    Cell*ptr = head;
    while(ptr!= NULL) {
        printf("%d\t", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

Cell* reverseLink(Cell*head) {
    Cell* pPrev, *pNext, *pCur;
    if(head == NULL || head->next == NULL)
        return NULL;
    pPrev = head;
    pCur = head->next;

    while(pCur != NULL) {
        pNext = pCur->next;
        pCur->next = pPrev;
        if(pPrev == head)
            pPrev->next = NULL;
        pPrev = pCur;
        pCur = pNext;
    }
    head = pPrev;
    return head;
}

Cell* reverseLink2(Cell*head) {
    Cell *tCell;
    Cell* listp = NULL, *ptr = head;
    if(head == NULL)
        return NULL;
    while(ptr != NULL) {
        tCell = (Cell*)malloc(sizeof(Cell));
        tCell->data = ptr->data;
        tCell->next = listp;
        listp = tCell;
        ptr = ptr->next;
    }
    printCellLink(listp);
    return listp;
}

int main(int argc, char** argv) {

    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Cell *head = (Cell*)malloc(sizeof(Cell));
    head = createLink(head, data, sizeof(data)/sizeof(int));
    printCellLink(head);
    head = reverseLink(head);
    printCellLink(head);
    reverseLink2(head);
    return 0;
}
