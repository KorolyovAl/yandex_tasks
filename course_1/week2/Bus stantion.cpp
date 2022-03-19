#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	string command;
	int Q;
	map <string, vector <string>> bus;
	map <string, vector <string>> stops;

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> command;

		if (command == "NEW_BUS") {
			int stop_count;
			string point, marsh;
			cin >> marsh >> stop_count;
			for (int i = 0; i < stop_count; i++) {
				cin >> point;
				bus[marsh].push_back(point);
				stops[point].push_back(marsh);
				point.clear();
			}
		}

		if (command == "BUSES_FOR_STOP") {
			string point;
			cin >> point;

			if (stops.find(point) != stops.end()) {
				for (auto i : stops[point]) {
					cout << i << " ";
				}
				cout << endl;
			}
			else {
				cout << "No stop" << endl;
			}

		}

		if (command == "STOPS_FOR_BUS") {
			string point, marsh;
			cin >> marsh;

			if (bus.find(marsh) != bus.end()) {
				for (auto point : bus[marsh]) {
					if (stops[point].size() > 1) {
						cout << "Stop " << point << ": ";
						for (auto i : stops[point]) {
							if (i != marsh)
								cout << i << " ";
						}
						cout << endl;
					}
					else {
						cout << "Stop " << point << ": "<< "no interchange" << endl;
					}
				}
			}
			else {
				cout << "No bus" << endl;
			}

		}

		if (command == "ALL_BUSES") {
			if (bus.size() != 0) {
				for (auto i : bus) {
					cout << "Bus " << i.first << ": ";
					for (auto n : bus[i.first]) {
						cout << n << " ";
					}
					cout << endl;
				}
			}
			else cout << "No buses" << endl;
		}
	}
	return 0;
}
