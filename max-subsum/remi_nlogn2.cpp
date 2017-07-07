/* https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
 * Complexity : O(n ln n)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;


int repr(vector<int> &uf, int i) {
    /* Gets representant of i in a union-find */
    if(uf[i] == i) {
        return i;
    }
    else {
        int p = repr(uf, uf[i]);
        return uf[i] = p;
    }
}

int main() {
    int Q;
    cin >> Q;
    for(int q=0 ; q < Q ; q++) {
        long m, n;
        cin >> n >> m;

        // gets cumulated value of the sequence
        vector<long> cumulated(n+1, 0);
        cumulated[0] = m;
        for(int i=1 ; i <= n ; i++) {
            long x;
            cin >> x;

            cumulated[i] = (cumulated[i-1] + x) % m;
        }

        /* A bijection in [0, n-i-1] so that cumulated[perm] is sorted
         * Indexes will be 'removed' progressively to refer only to the last values of cumulated.
         */
        vector<int> perm(n+1);
        for(int i=0 ; i <= n ; i++) {
            perm[i] = i;
        }
        sort(begin(perm), end(perm), [cumulated](int a, int b) {
            return cumulated[a] > cumulated[b];
        });
        /* Process an inversion of permutation perm */
        vector<int> perm_index(n+1);
        for(int i=0 ; i <= n ; i++) {
            perm_index[perm[i]] = i;
        }

        /* To remove indexes, constructs a union-find to redirect to another value
         * We will keep cumulated[repr(uf, perm[...])] sorted
        */
        vector<int> uf(n+1);
        for(int i=0 ; i <= n ; i++) {
            uf[i] = i;
        }

        int to_ins = n;
        long glob_max = cumulated[perm[0]];
        for(int i=n ; i >= 0 ; i--) {
            long cur_val = cumulated[perm[i]];

            // glob_max = max(glob_max, cur_val);

            /* Let's find best value of added where (added + cumulated[i] < m */
            while(m - cumulated[repr(uf, perm[to_ins])] + cur_val >= m)
                to_ins--;
            glob_max = max(glob_max, m - cumulated[repr(uf, perm[to_ins])] + cur_val);
        }

        cout << glob_max << endl;
    }
}
