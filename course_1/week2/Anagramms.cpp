#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	string first;
	string second;
	vector <char> check_one;
	vector <char> check_two;
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		first.clear(); second.clear();
		check_one.clear(); check_two.clear();
		cin >> first >> second;

		if (first.size() == second.size()) {
			for (unsigned step = 0; step < first.size(); step++) {
				check_one.push_back(first[step]);
			}
			for (unsigned step = 0; step < second.size(); step++) {
				check_two.push_back(second[step]);
			}
			sort (check_one.begin(), check_one.end());
			sort (check_two.begin(), check_two.end());

			if (check_one == check_two) cout << "YES" << endl;
			else cout << "NO" << endl;

		}
		else cout << "NO" << endl;

	}

	return 0;
}
