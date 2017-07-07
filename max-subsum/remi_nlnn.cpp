/* https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
 * Complexity : O(n^2)
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


int i_search(vector<long> &seq, vector<int> &perm, long add, long m) {
    /* Search for the last i so that seq[perm[i]] + add < m */
    int l = 0;
    int r = seq.size();

    while(r-l > 1) {
        int mid = (l + r) / 2;
        if(seq[perm[mid]] + add >= m) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    return l;
}

int main() {
    int Q;
    cin >> Q;
    for(int q=0 ; q < Q ; q++) {
        long m, n;
        cin >> n >> m;

        // gets cumulated value of the sequence
        vector<long> cumulated(n+1, 0);
        for(int i=1 ; i <= n ; i++) {
            long x;
            cin >> x;

            cumulated[i] = (cumulated[i-1] + x) % m;
        }

        // builds a permutation so that cumulated[perm] is sorted
        vector<int> perm(n+1);
        for(int i=0 ; i <= n ; i++) {
            perm[i] = i;
        }
        sort(begin(perm), end(perm),  [cumulated](int a, int b) {
            return cumulated[a] < cumulated[b];
        });

        // looks for best subset
        long max_sum = -1;
        for(int i=0 ; i <= n ; i++) {
            // The maximum element j so that cumulated[perm[j]] + m-cumulated[i] < m
            int mid_max = i_search(cumulated, perm, m-cumulated[i], m);
            if(perm[mid_max] > i) {
                // our maximum value is actually on right part of i
                max_sum = max(max_sum, (m + cumulated[perm[mid_max]]) % m);
            }
            if(perm[n] > i) {
                max_sum = max(max_sum, (m + cumulated[perm[i]]) % m);
            }
        }

        cout << max_sum << endl;
    }
}
