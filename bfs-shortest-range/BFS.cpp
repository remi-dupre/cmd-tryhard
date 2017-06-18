#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int q; cin >> q;
    for(int z =0; z < q; z++){
        int n,m; cin >> n >> m;
        vector<list<int>> edges(n);
        for(int i = 0; i < m; i++){
            int u,v; cin >> u >> v;
            edges[u-1].push_back(v); edges[v-1].push_back(u);
        }
        int s; cin >> s;
        int nb_dec = 1;
        vector<int> dist(n);
        for(int i =0; i < n; i++){dist[i] = -1;} dist[s-1] = 0;
        list<int> nodes = {s};
        while((nb_dec < n) && (not nodes.empty())){
            int current = nodes.front();
            nodes.pop_front();
            for(int i : edges[current-1]){
                if (dist[i-1]==-1){
                    nb_dec++; nodes.push_back(i);
                    dist[i-1] = dist[current-1]+6;
                }
            }
        }
        for(int i = 0; i < n; i++) if (i+1!=s) cout << dist[i] << " ";
        cout << endl;
    }
    
    return 0;
}
