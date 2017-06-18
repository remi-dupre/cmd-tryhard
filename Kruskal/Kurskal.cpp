#include <cmath>
#include <cstdio>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
using namespace std;

bool befo(tuple<int,int,int> a,tuple<int,int,int> b){
    int x_a,x_b,y_a,y_b,r_a,r_b;
    tie(x_a,y_a,r_a) = a;
    tie(x_b,y_b,r_b) = b;
    if (r_a < r_b) return true;
    if (r_a > r_b) return false;
    return (x_a+y_a+r_a) < (x_b+y_b+r_b);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,m; cin >> n >> m;
    vector<tuple<int,int,int>> edges;
    for(int i = 0; i < m; i++){
        int x,y,r; cin >> x >> y >> r;
        edges.push_back(make_tuple(x,y,r));
    }
    vector<int> discovered(n+1);
    for (int i = 1;i <= n; i++) discovered[i]= -1;
    sort(edges.begin(),edges.end(),befo);
    int sum = 0;
    for(int a = 0; a < m; a++){
        int x,y,r;
        tie(x,y,r) = edges[a];
        //cout << x << " " << y << " " << r << " \n";
        if ((discovered[x]==-1) && (discovered[y]==-1)){
            discovered[x] = x;
            discovered[y] = x;
            sum += r;
        }
        else if (discovered[x]==-1){
            discovered[x] = discovered[y];
            sum += r;
        }
        else if (discovered[y]==-1){
            discovered[y] = discovered[x];
            sum += r;
        }
        else if (discovered[x] != discovered[y]){
            int s = discovered[x];
            for(int i = 1; i <= n; i++) if (discovered[i] == s) discovered[i] = discovered[y];
            sum += r;
        }
        else{
            //cout << x << " " << y <<" non prise \n";
        }
        
    }
    cout << sum << endl;
    
    
    return 0;
}
