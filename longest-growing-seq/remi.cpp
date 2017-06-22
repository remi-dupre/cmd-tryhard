#include <iostream>
#include <vector>

using namespace std;


int search(const vector<int> &tab, const vector<int> &tab_vals, int val, int min=-1, int max=-1) {
	// Returns maximum index i so that tab_vals[tab[i]] <= val
	// Initialisation of arguments
	if(min == -1) {
		min = 0;
		max = tab.size();
	}
	// Dichotomie
	if(max - min == 1) {
		return min;
	}
	else if(max - min > 1) {
		int mid = (max + min) / 2;
		if(tab_vals[tab[mid]] >= val) {
			return search(tab, tab_vals, val, min, mid);
		}
		else {
			return search(tab, tab_vals, val, mid, max);
		}
	}
	return -1;
}

int main() {
	int N;
	cin >> N;

	// Inputs sequence
	vector<int> seq(N);
	for(int i=0 ; i < N ; i++) {
		cin >> seq[i];
	}

	// Contains the minimum end for a sequence of length
	vector<int> min_end(1, 0);

	for(int i=0 ; i < N ; i++) {
		// searchs for the longest sequence ending with less than seq[i]
		int max_seq = search(min_end, seq, seq[i]);
		if(max_seq == min_end.size()-1) {
			// One unit longer
			min_end.push_back(i);
		}
		else {
			// Enhance a previous result
			min_end[max_seq+1] = i;
		}
	}

	cout << min_end.size() - 1 << endl;
}

// https://www.hackerrank.com/challenges/longest-increasing-subsequent

