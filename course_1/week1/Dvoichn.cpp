#include <iostream>
#include <vector>
#include <algorithm> // for use "reverse"
using namespace std;

int main() {
	int a;
	vector <int> ch;
	cin >> a;
	while (a >= 2) {
		ch.push_back(a%2);
		a /= 2;
	}
	ch.push_back(a);
	reverse (ch.begin(), ch.end());	// reverse of vector
	for (int x : ch) cout << x;
	return 0;
}
