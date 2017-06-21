#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


int repr(vector<int> &uf, int u) {
    /* Returns representant of u in the union-find uf */
    if(uf[u] == u) {
        return u;
    }
    else {
        uf[u] = repr(uf, uf[u]);
        return uf[u];
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    int x, y, r;
    vector<tuple<int, int, int>> G;
    for(int i=0 ; i < M ; i++) {
        cin >> x >> y >> r;
        G.push_back(make_tuple(x-1, y-1, r));
    }

    // Sorts nodes with correct priority
    sort(begin(G), end(G), [](auto &v1, auto &v2) {
        int x1, x2, y1, y2, r1, r2;
        tie(x1, y1, r1) = v1;
        tie(x2, y2, r2) = v2;

        if(r1 != r2) {
            return r1 < r2;
        }
        else {
            return (x1 + y1 + r1) < (x2 + y2 + r2);
        }
    });

    // Initiate a union-find keeping inventory of classes
    vector<int> uf(N);
    for(int i=0 ; i < N ; i++) {
        uf[i] = i;
    }

    // Greedy algorithm
    int total_weight = 0;
    for(auto &v : G) {
        tie(x, y, r) = v;
        if(repr(uf, x) != repr(uf, y)) {
            total_weight += r;
            uf[repr(uf, x)] = repr(uf, y); // Joins the two classes
        }
    }

    cout << total_weight << endl;
}

// https://www.hackerrank.com/challenges/kruskalmstrsub
