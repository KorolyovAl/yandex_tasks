#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

int main() {
	map <string, set<string>> key_word1;
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		string command;
		cin >> command;

		if (command == "ADD") {
			string word1;
			string word2;
			cin >> word1 >> word2;

			key_word1[word1].insert(word2);
			key_word1[word2].insert(word1);
			word1.clear();
			word2.clear();
		}
		if (command == "COUNT") {
			string word;
			cin >> word;

			cout << key_word1[word].size() << endl;
			word.clear();
		}
		if (command == "CHECK") {
			string word1;
			string word2;
			cin >> word1 >> word2;

			if (key_word1[word1].count(word2) || key_word1[word2].count(word1)) {
				cout << "YES" << endl;
			}
			else cout << "NO" << endl;
		}
	}
	return 0;
}
