#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool IsPalindrom (string a) {
	if (a.length() == 0) return true;
	string b = a;
	reverse (a.begin(), a.end());
	if (a == b) return true;
	else return false;
}

int main() {
	string a;
	cin >> a;
	cout << IsPalindrom (a);
	return 0;
}
