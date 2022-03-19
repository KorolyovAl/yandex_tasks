#include <iostream>
#include <vector>
using namespace std;

void Reverse (vector <int>& v) {
	vector <int> a;
	unsigned step = 0;
	for (unsigned i = v.size() - 1; i < v.size() && i >= 0; i = v.size() - 1 - step) {
		a.push_back(v[i]);
		step++;
	}
	v = a;
	a.clear();
}
int main() {
	vector <int> v;
	Reverse (v);
	return 0;
}
