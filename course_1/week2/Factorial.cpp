#include <iostream>
using namespace std;

int Factorial (int a) {
	int i = 1, f = 1;
	if (a > 0) {
		while (i <= a) {
			f *= i;
			i++;
		}
		return f;
	}
	else return 1;
}

int main() {
	int a;
	cin >> a;
	cout << Factorial(a);
	return 0;
}
