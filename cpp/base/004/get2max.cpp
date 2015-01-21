#include <iostream>
using namespace std;

void get2Max(int arr[], int arr_size) {
    int i, max = 0, smax = 0, max_index = 0, smax_index = 0;
    for(i = 0; i < arr_size; i++) {
        if(max <= arr[i]) {
            smax = max;
            smax_index = max_index;
            max = arr[i];
            max_index = i;
        }else if(smax < arr[i]) {
            smax = arr[i];
            smax_index = i;
        }
        cout<<"======================="<<i<<"======================="<<endl;
        cout<<"Max:"<<max<<" Second Max:"<<smax<<endl;
        cout<<"Max Index:"<<max_index<<" Second Max Index:"<<smax_index<<endl;
    }
}

int main(int argc, char* argv[]) {
    int arr[] = {22, 2, 4, 62, 80, 32, 22};
    get2Max(arr, 7);
    return 0;
}
