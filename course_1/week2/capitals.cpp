#include <iostream>
#include <map>
using namespace std;

int main() {
	map <string, string> guide;
	string command;
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			string country, new_capital;
			cin >> country >> new_capital;
			auto it = guide.find(country);

			if (it != guide.end()) {
				if (new_capital == guide[country]) {
					cout << "Country " << country << " hasn't changed its capital" << endl;
				}
				else {
					cout << "Country " << country << " has changed its capital from " << guide[country]
						<< " to " << new_capital << endl;
					guide[country] = new_capital;
				}
			}
			else {
				guide[country] = new_capital;
				cout << "Introduce new country "<< country << " with capital " << new_capital << endl;
			}

		}

		if (command == "RENAME") {
			string country, new_country;
			cin >> country >> new_country;
			auto it = guide.find(country);

			if (it == guide.end() || country == new_country || guide.find(new_country) != guide.end()) {
				cout << "Incorrect rename, skip" << endl;
			}
			else {
				cout << "Country " << country << " with capital " << guide[country]
				     << " has been renamed to " << new_country << endl;
				guide[new_country] = guide[country];
				guide.erase(country);
			}
		}

		if (command == "ABOUT") {
			string country;
			cin >> country;
			auto it = guide.find(country);

			if (it != guide.end()){
				cout << "Country " << country << " has capital " << guide[country] << endl;
			}
			else {
				cout << "Country " << country << " doesn't exist" << endl;
			}
		}

		if (command == "DUMP") {
			if (guide.size() > 0) {
				for (auto i : guide) {
					cout << i.first << "/" << i.second << " ";
				}
				cout << endl;
			}
			else {
				cout << "There are no countries in the world" << endl;
			}
		}

	}

	return 0;
}
