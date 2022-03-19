#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector <string> PalindromFilter (vector <string> words, int minLenght) {
	vector <string> palindrom;
	string check;
	for (unsigned step = 0; step < words.size(); ++step) {
		check = words[step];
		int prov = 1;
		for (unsigned i = 0; i < check.size()/2; ++i) {
			if (check[i] != check[check.size() - 1 - i]) prov = 0;
		}
		if (prov == 1 && check.size() >= minLenght ) palindrom.push_back(check);
	}
	return palindrom;
}

int main() {
	vector <string> words;
	int minLenght;
	PalindromFilter (words, minLenght );
	return 0;
}
