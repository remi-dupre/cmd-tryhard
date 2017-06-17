#include <iostream>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;


int main() {
    int q, n, m, u, v;
    cin >> q;
    for(int i_q=0 ; i_q < q ; i_q++) {
        cin >> n >> m;

        // Building the graph
        vector<vector<int>> G(n+1);
        for(int i=0 ; i < m ; i++) {
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        // Processing distances
        int root, s, s_dist;
        cin >> root;
        vector<int> dist(n+1, -1); // non visited nodes have a distance of -1
        queue<tuple<int, int>> to_visit;
        // Starts BFS from `root`
        dist[root] = 0;
        to_visit.push(make_tuple(root, dist[root]));
        while(!to_visit.empty()) {
            tie(s, s_dist) = to_visit.front();
            for(int son : G[s]) {
                if(dist[son] == -1) {
                    // The son hasn't been visited
                    dist[son] = s_dist + 6;
                    to_visit.push(make_tuple(son, dist[son]));
                }
            }
            to_visit.pop();
        }

        // Outputs the distances
        for(int i=1 ; i <= n ; i++) {
            if(i != root) {
                cout << dist[i] << ' ';
            }
        }
        cout << endl;
    }
}

// https://www.hackerrank.com/challenges/bfsshortreach/problem
