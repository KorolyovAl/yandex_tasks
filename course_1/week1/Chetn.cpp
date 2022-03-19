#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if (a <= b && a >= 1 && b <= 30000) {
		for (int i = a; i <= b; i++) {
			if  (i % 2 == 0) cout << i << " ";
		}
	}

	return 0;
}
