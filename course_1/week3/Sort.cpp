#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp (int a, int b) {
	if (abs(a) < abs(b)) {
		return true;
	}
	else return false;
}

int main() {
	int N = 0;
	vector <int> v;
	int a;
	cin >> N;
	if (N >= 0 && N <= 1000 ) {
		for (int i = 0; i < N; i++) {
			cin >> a;
			if (a >= -1000000 && a <= 1000000)
				v.push_back(a);
		}

		sort(begin(v), end(v), comp);
		for (auto i : v) {
			cout << i << " ";
		}
	}
	return 0;
}
