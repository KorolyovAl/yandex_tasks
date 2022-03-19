#include <iostream>
#include <cmath>
using namespace std;

int main() {
	double a, b, c, x1, x2, d;
	cin >> a >> b >> c;
	d = b*b - 4*a*c;
	if (a == 0. && b == 0.) {

	}
	if (a == 0. && b != 0. ) {
		x1 = -c/b;
		cout << x1;
	}
	if (a != 0. ) {
		if (d > 0.) {
			x1 = (-b + sqrt(d))/(2.*a);
			x2 = (-b - sqrt(d))/(2.*a);
			cout << x1 << " " << x2;
		}
		if (d == 0.) {
			x1 = -b/(2.*a);
			cout << x1;
		}
	}
	return 0;
}
