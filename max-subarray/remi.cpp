#include <iostream>
#include <stdlib.h>

using namespace std;


#define MIN_VAL -10001

int main() {
    int T, N;
    cin >> T;
    for(int t=0 ; t < T ; t++) {
        cin >> N;

        int max_fly = MIN_VAL; // answer for non contiguous sum
        int max_con = MIN_VAL; // answer for contiguous sum
        int cur_con = MIN_VAL; // curent contiguous sum

        for(int n=0 ; n < N ; n++) {
            int x;
            cin >> x;

            // max non contiguous is sum of positive numbers
            if(x > 0) {
                if(max_fly < 0) {
                    // x is the first positive value
                    max_fly = 0;
                }
                max_fly += x;
            }
            else if(x > max_fly) {
                // if all values are negatives, takes the greatest one
                max_fly = x;
            }


            // check if current contiguous sum would remain positive
            if(cur_con < 0) {
                cur_con = x;
            }
            else {
                cur_con += x;
            }

            if(cur_con > max_con) {
                max_con = cur_con;
            }
        }

        printf("%d %d\n", max_con, max_fly);
    }
}
