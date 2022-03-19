#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector <int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	vector <vector<string>> busineses (months[0]);
	int day = 0, month = 0, Q;

	string command;
//	cout << "Q = ";
	cin >> Q;

	for (int i = 0; i < Q; i++) {
//		cout << " command = ";
		cin >> command;
		if (command == "ADD") {
			string business;
//			cout << "day and business =  " << endl;
			cin >> day >> business;
			busineses[day-1].push_back(business);
		}
		if (command == "DUMP") {
			cin >> day;
			cout << busineses[day-1].size() << " ";
			for (auto step : busineses[day-1]) cout << step << " ";
			cout << endl;
		}
		if (command == "NEXT") {
			month++;
			if (month > 11) month -= 12;
//			cout << "month = " << month << endl;
			vector <string> v;
			if (months[month] > months[month-1] && month != 0) {
				for (int day_number = months[month-1]+1; day_number <= months[month]; day_number++) {
					busineses.push_back(v);
				}

			}
			if (months[month] < months[month-1] && month != 0) {
				string line;
				int a = months[month];
//				cout << "a = " << a << endl;
				for (int step2 = busineses.size()-1 ; step2 >= a; step2-- ) {
					for (auto step3 : busineses[step2]) {
						line = step3;
//						cout << "line = " << line << endl;
						busineses[a-1].push_back(line);
					}
					busineses.pop_back();
				}
			}
		}
		if (command == "PRINT") {
			cout << busineses.size();
		}
	}
	return 0;
}
