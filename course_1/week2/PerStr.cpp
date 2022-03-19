#include <iostream>
#include <vector>
using namespace std;

void MoveStrings (vector <string>& source, vector <string>& destination) {
	for (unsigned step = 0; step < source.size(); step++ ) {
		destination.push_back(source[step]);
	}
	source.clear();
}

int main() {
	vector <string> source = {"a", "b", "c"};
	vector <string> destination = {"z"};
	MoveStrings (source, destination);
	return 0;
}
