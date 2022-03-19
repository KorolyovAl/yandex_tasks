#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
	set <string> lines;
	string line;
	int N;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> line;
		lines.insert(line);
		line.clear();
	}

	cout << lines.size();

	return 0;
}
