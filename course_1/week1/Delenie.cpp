#include <iostream>
using namespace std;

int main() {
	double a, b;
	int c;
	cin >> a >> b;
	if (b == 0.) {
		cout << "Impossible";
	}
	else {
		c = a / b;
		cout << c;
	}
	return 0;
}
