#include <iostream>
#include <vector>
using namespace std;

vector <int> Reversed (const vector <int>& v) {
	vector <int> a;
	unsigned step = 0;
	for (unsigned i = v.size() - 1; i < v.size() && i >= 0; i = v.size() - 1 - step) {
		a.push_back(v[i]);
		step++;
	}
	return a;
}
int main() {
	vector <int> v;
	Reversed (v);
	return 0;
}
