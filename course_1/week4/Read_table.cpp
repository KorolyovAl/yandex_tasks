#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
	int Q;
	int N;
	int a;
	ifstream input("input.txt");

	input >> Q >> N;
	for (int i = 0; i < Q; i++) {
		for (int z = 0; z < N; z++) {
			input >> a;
			if (z != (N - 1)) cout << setw(10) << a << " ";
			else cout << setw(10) << a;
			input.ignore(1);
		}
		if (i != (Q - 1))cout << endl;
	}

	return 0;
}
