#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	string command;
	vector <int> turn;
	int Q{0}, count{0};
	cin >> Q;
	for (int step1 = 0; step1 < Q; step1++) {
	cin >> command;

	if (command == "COME") {	// the queue increases by count
		cin >> count;
		if (count > 0) {
			for (int step = 0; step < count; step++) turn.push_back(0);	// 0 is quiet, 1 is worry
		}
		if (count <= 0) {
			for (int step = 0; step < count * -1; step++) turn.pop_back();
		}
	}
	if (command == "WORRY") {
		cin >> count;
		turn[count] = 1;
		}
	if (command == "QUIET") {
		cin >> count;
		turn[count] = 0;
		}
	if (command == "WORRY_COUNT") {
		int worry_count = 0;
		for (auto z : turn) {
			if (z == 1) worry_count++;
		}
		cout << worry_count << endl;
		}
	if (command == "PRINT") {
		for (auto z : turn) cout << z << " ";
		cout << endl;
	}
	}
	return 0;
}
