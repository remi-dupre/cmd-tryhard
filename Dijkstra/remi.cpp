#include <iostream>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;


int main() {
    int T, N, M, x, y, r, S;
    cin >> T;
    for(int t=0 ; t < T ; t++) {
        // Building graph
        cin >> N >> M;
        vector<vector<tuple<int, int>>> G(N);
        for(int m=0 ; m < M ; m++) {
            cin >> x >> y >> r;
            x--; y--;
            G[x].push_back(make_tuple(r, y));
            G[y].push_back(make_tuple(r, x));
        }
        cin >> S;
        S--;

        // Decreasing priority queue
        priority_queue<tuple<int, int>,
            vector<tuple<int, int>>,
            greater<tuple<int, int>>> node_pool;

        node_pool.push(make_tuple(0, S)); // S is at a distance 0 from S
        vector<int> dist(N, -1);
        while(!node_pool.empty()) {
            tie(r, x) = node_pool.top();
            node_pool.pop();

            // Adds every neighbour of updated node
            if(dist[x] == -1) {
                count ++;
                dist[x] = r;
                for(tuple<int, int> &V : G[x]) {
                    tie(r, y) = V;
                    if(dist[y] == -1)
                        node_pool.push(make_tuple(dist[x] + r, y));
                }
            }
        }

        // Shows result
        for(int n=0 ; n < N ; n++) {
            if(n != S) {
                cout << dist[n] << ' ';
            }
        }
        cout << endl;
    }
}

// https://www.hackerrank.com/challenges/dijkstrashortreach
