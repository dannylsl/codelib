#include <iostream>
using namespace std;

class Node{
    public:
        void set_value(int value);
        int get_value();
        Node* next;
    private:
        int value;
};

inline void Node::set_value(int value) {
    this->value = value;
    this->next  = NULL;
}


inline int Node::get_value() {
    return this->value;
}

class LoopList {
    public:
        LoopList();
        int get_length();
        void add_node(Node *nd);
        void rotate();
        Node* head;
        Node* foot;
    private:
        int length;
};

LoopList::LoopList() {
    this->length = 0;
    this->head = NULL;
    this->foot = NULL;
}

inline int LoopList::get_length() {
    return this->length;
}

void LoopList::add_node(Node *nd) {
    if( NULL == this->head) {
        this->head = nd;
        this->foot = nd;
        this->foot->next = this->head;
    }else {
        this->foot->next = nd;
        this->foot = nd;
        this->foot->next = this->head;
    }
    this->length++;
}

void LoopList::rotate() {
    this->head = this->head->next;
    this->foot = this->foot->next;
}

void print_looplist(LoopList *lp) {
    int i, len = lp->get_length();
    Node* ptr = lp->head;
    for(i = 0; i < len ; i++) {
        cout<<ptr->get_value()<<" ";
        ptr = ptr->next;
    }
    cout<<endl;
}

int get_sum(LoopList *lp, int N) {
    int i;
    int sum = 0;
    Node* ptr = lp->head;
    for(i = 0; i < N; i++) {
        sum += (i+1) * ptr->get_value();
        ptr = ptr->next;
    }
    return sum;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void print_ar(int ar_size, int * ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        cout<<ar[i]<<" ";
    }
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

int get_max_PMEAN(int ar_size, int *ar) {
    int max, i;
    max = ar[0];
    for(i = 0; i < ar_size; i++) {
        if(ar[i] > max )
            max = ar[i];
    }
    return max;
}

int main(int argc, char* argv[]) {
    int N,value,i;
    cin>>N;
    int PMEAN[N];
    LoopList* lp = new LoopList();
    Node *node;
    for(i = 0; i < N; i++) {
        node = new Node();
        cin>>value;
        node->set_value(value);
        lp->add_node(node);
    }

    for(i = 0; i < N; i++) {
        PMEAN[i] = get_sum(lp, N);
        lp->rotate();
    }

//    quickSort(N,PMEAN);
//    cout<<PMEAN[N-1] <<endl;
    cout << get_max_PMEAN( N, PMEAN);
    return 0;
}
