#include <iostream>
#include <string>

using namespace std;

int main() {
	string a, b, c;
	cin >> a >> b >> c;
	if (a < b) {
		if (a < c) {
			cout << a;
		}
		else {
			if (c < b) cout << c;
			else cout << b;
		}
	}
	else {
		if (b < c)
			cout << b;
		else cout << c;
	}
}
