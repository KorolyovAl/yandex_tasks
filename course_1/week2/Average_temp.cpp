#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, average, k{0};
	cin >> n;
	vector <int> temp (n);
	for (int z = 0; z < n; z++) {
		cin >> temp[z];
	}
	for ( auto c : temp ) {
		k += c;
	}
	average = k / n;
	k = 0;
	for (auto q : temp) {
		if (q > average) k++;
	}
	cout << k << endl;
	for (int i = 0; i < n; i++) {
		if (temp[i] > average) cout << i << " ";
	}
	return 0;
}
