#include <iostream>
#include <cstring>
using namespace std;

#define STONE_MAX 100

int main(int argc, char * argv[]) {
    int n;
    cin>>n;
    char stones[n][STONE_MAX];
    int i,j, stonelen, result = 0;
    int ch[26] = {0}, flag[26] = {0};

    for(i = 0; i < n; i++) {
        cin>>stones[i];

        stonelen = strlen(stones[i]);
        memset(flag, 0, 26 * sizeof(int));
        for(j = 0; j < stonelen; j++) {
            int index = stones[i][j] - 'a';
            if(flag[index] == 0) {
                ch[index]++;
                flag[index]++;
            }
        }
//        cout<<stones[i]<<endl;
    }

    for(i = 0; i < 26; i++) {
        cout<<(char)(i+'a')<<" "<<ch[i]<<endl;
        if(ch[i] == n)
            result++;
    }
    cout<<result<<endl;;
    return 0;
}
