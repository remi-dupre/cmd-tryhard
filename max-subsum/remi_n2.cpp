/* https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
 * Complexity : O(n^2)
 */

#include <iostream>
#include <vector>

using namespace std;


int main() {
    int Q;
    cin >> Q;
    for(int q=0 ; q < Q ; q++) {
        long int m, n;
        cin >> n >> m;

        // gets cumulated value of the sequence
        vector<long int> cumulated(n+1, 0);
        for(int i=1 ; i <= n ; i++) {
            long int x;
            cin >> x;

            cumulated[i] = (cumulated[i-1] + x) % m;
        }

        // looks for best subset
        long int max_sum = -1;
        for(int i=0 ; i <= n ; i++) {
            for(int j=i+1 ; j <= n ; j++) {
                long int sub_sum = (m + cumulated[j] - cumulated[i]) % m;
                if(sub_sum > max_sum) {
                    max_sum = sub_sum;
                }
            }
        }

        cout << max_sum << endl;
    }
}
