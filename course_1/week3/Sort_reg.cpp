#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
	int N = 0;
	string S;
	vector <string> v;
	cin >> N;
	if (N >= 0 && N <= 1000) {
		for (int i = 0; i < N; i++) {
			cin >> S;
			if (S.size() >= 1 && S.size() <= 15) {
				v.push_back(S);
			}
			S.clear();
		}

		  sort(begin(v), end(v), [](string l, string r) {
			  string l1, r1;
			  for (auto i : l) {
				 i = tolower(i);
				  l1.push_back(i);
			  }
			  for (auto x : r) {
				  x = tolower(x);
				  r1.push_back(x);
			  }
//			  cout << "l1 = " << l1 << " r1 = " << r1 << endl;
			  return l1 < r1;
			   }
		  );

		  for (auto x : v) {
			  cout << x << " ";
		  }
	}

	return 0;
}
