#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
/*
 * * Complete the function below.
 * */
int maxDifference(vector < int > a) {
    int i,j;
    int max = 0;

    for(i = a.size()-1; i > 0; i--) {
        for(j = i - 1; j > 0; j--) {
            if(a[i] <= a[j]) {
                continue;
            }
            if( a[i] - a[j] > max) {
                max = a[i] - a[j];
            }
        }
    }
    return max;
}
int main() {
    vector < int > ar(6) = {7,2,3,10,2,8};
    cout<<maxDifference(ar);
    return 0;
}
