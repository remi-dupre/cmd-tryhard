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

        /* A bijection in [0, n-i-1] so that cumulated[perm[]] is sorted
         * Indexes will be 'removed' progressively to refer only ranges on the left of current index
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

        long glob_max = 0;
        for(int i=n ; i > 0 ; i--) {
            /* Exclude the i^th element from available left range */
            int ordered_i = perm_index[i];  // i = perm[ordered_i]
            uf[repr(uf, perm[ordered_i])] = repr(uf, perm[ordered_i-1]);

            /* Let's find best value of added where added + cumulated[i] < m */
            int left = 0, right = n+1;
            while(right - left > 1) {
                int mid = (left + right + 1) / 2;
                int val_mid = m - cumulated[repr(uf, perm[mid])];
                if(val_mid + cumulated[i] < m) {
                    left = mid;
                }
                else {
                    right = mid;
                }
            }

            int val_added = (m - cumulated[repr(uf, perm[left])]);
            glob_max = max(glob_max, (val_added + cumulated[i]));
        }

        cout << glob_max << endl;
    }
}
