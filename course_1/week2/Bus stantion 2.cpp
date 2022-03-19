#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	string command;
	int Q;
	map <vector <string>, int> bus;
	vector <string> stops;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int stop_count;
		string point;
		cin >> stop_count;
		for (int i = 0; i < stop_count; i++) {
			cin >> point;
			stops.push_back(point);
			point.clear();
		}

		if (bus.find(stops) != bus.end()) {
			cout << "Already exists for " << bus[stops] << endl;
		}
		else {
			int size = bus.size();
			bus[stops] = size + 1;
			cout << "New bus " << size + 1 << endl;
		}
		stops.clear();
	}
	return 0;
}
