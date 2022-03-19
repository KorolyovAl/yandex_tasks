#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings {
	public:
		void AddString (const string& line) {
			v.push_back(line);
		}
		vector<string> GetSortedStrings() {
			sort(begin(v), end(v));
			return v;
		}
	private:
		vector <string> v;
};

void PrintSortedStrings (SortedStrings& line) {
	for (const string& s : line.GetSortedStrings()) {
		cout << s << " ";
	}
	cout << endl;
}

int main() {

	SortedStrings string;
	string.AddString("first");
	string.AddString("second");
	string.AddString("third");
	string.AddString("second");

	PrintSortedStrings(string);

	return 0;
}
