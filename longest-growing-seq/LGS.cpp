#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

void dicho(int x,vector<int> &sub,int i,int j){
    int m = (i+j)/2;
    if (sub[m] < x) {
        if (sub[m+1] > x) sub[m+1] = x;
        else dicho(x,sub,m+1,j);
    }
    else if (sub[m] > x) dicho(x,sub,i,m);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N; cin >> N;
    vector<int> seq(N);
    for(int i = 0; i < N; i++) cin >> seq[i];
    int infini_minus = std::numeric_limits<int>::min();
    vector<int> sub;
    sub.push_back(infini_minus);
    int n = 1;
    for(int i = 0; i < N; i++){
        if (seq[i] > sub.back()){
            sub.push_back(seq[i]);
            n += 1;
        }
        else if (seq[i] < sub.back()) dicho(seq[i],sub,0,n-1);
    }
    cout << n-1;

    return 0;
}
