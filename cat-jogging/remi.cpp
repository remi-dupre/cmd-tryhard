#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


int main() {
    int N, M, x, y;
    cin >> N >> M;

    vector<vector<int>> G(N);
    for(int m=0 ; m < M ; m++) {
        cin >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    // calculates number of paths of length 2 from x to y -> O((V + N)*V)
    unsigned long int nb_cycles = 0;
    for(int x=0 ; x < N ; x++) {
        vector<unsigned long int> nb_d2(N, 0);
        for(int z : G[x]) {
            for(int y : G[z]) {
                if(x != y)
                    nb_d2[y]++;
            }
        }
        for(int y=0 ; y < N ; y++) {
            nb_cycles += nb_d2[y] * (nb_d2[y] - 1);
        }
    }
    cout << nb_cycles / 8 << endl;
}

// https://www.hackerrank.com/challenges/cat-jogging?h_r=internal-search
