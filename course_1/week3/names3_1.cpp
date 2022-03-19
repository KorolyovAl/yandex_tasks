#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

vector <string> FindNameByHistory(const map<int, string>& names, int year) {
	vector <string> history_names;
	string name;
	string check;
	for (const auto& item : names) {
		if (item.first <= year && item.second != check) {
			history_names.push_back(item.second);
		}
		check = item.second;
	}
	if (history_names.size() >= 1) {
		history_names.pop_back();
	}
	return history_names;
}

class Person {
public:
	Person (const string& new_first_name,
			const string& new_last_name,
			const int& new_birth_year) {
		birth_year = new_birth_year;
		first_names[new_birth_year] = new_first_name;
		last_names[new_birth_year] = new_last_name;
	}
  void ChangeFirstName(int year, const string& first_name) {
		if (year >= birth_year)
			first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
		if (year >= birth_year)
			last_names[year] = last_name;
  }
  string GetFullName(int year) const {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "No person";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name;

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name;

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }
  string GetFullNameWithHistory(int year) const {
    // получить все имена и фамилии по состоянию на конец года year
	  vector <string> history_first_names;
	  vector <string> history_last_names;
	  history_first_names = FindNameByHistory(first_names, year);
	  history_last_names = FindNameByHistory(last_names, year);
/*	  cout << "elements of first names: ";
	  for (auto x : history_first_names) {
		  cout << x << " ";
	  }
	  cout << endl;*/
	    // получаем имя и фамилию по состоянию на год year
	    const string first_name = FindNameByYear(first_names, year);
	    const string last_name = FindNameByYear(last_names, year);

	    // если и имя, и фамилия неизвестны
	    if (first_name.empty() && last_name.empty()) {
	      return "No person";

	    // если неизвестно только имя
	    } else if (first_name.empty()) {
	    	if (history_last_names.size() >= 1) {
				string out = "(";
				int turn = 0;
				for (int i = history_last_names.size() - 1; i >= 0; i--) {
					if (turn == 0) {
						out += history_last_names[i];
					}
					else out += ", " + history_last_names[i];
					turn++;
				}
				out +=")";
				return last_name + " " + out;
	    	}
	      return last_name;

	    // если неизвестна только фамилия
	    } else if (last_name.empty()) {
	    	if (history_first_names.size() >= 1) {
				string out = "(";
				int turn = 0;
				for (int i = history_first_names.size() - 1; i >= 0; i--) {
					if (turn == 0) {
						out += history_first_names[i];
					}
					else out += ", " + history_first_names[i];
					turn++;
				}
				out +=")";
				return first_name + " " + out;
	    	}
	      return first_name;

	    // если известны и имя, и фамилия
	    } else {
	    	if (history_first_names.size() >= 1 || history_last_names.size() >= 1) {
	    		string out_first, out_last;
	    		if (history_first_names.size() >= 1) {
					out_first = "(";
					int turn = 0;
					for (int i = history_first_names.size() - 1; i >= 0; i--) {
						if (turn == 0) {
							out_first += history_first_names[i];
						}
						else out_first += ", " + history_first_names[i];
						turn++;
					}
					out_first +=") ";
	    		}
	    		if (history_last_names.size() >= 1) {
					int turn = 0;	out_last = " (";
					for (int i = history_last_names.size() - 1; i >= 0; i--) {
						if (turn == 0) {
							out_last += history_last_names[i];
						}
						else out_last += ", " + history_last_names[i];
						turn++;
					}
					out_last += ")";
	    		}
				return first_name + " " + out_first + last_name + out_last;
	    	}

	      return first_name + " " + last_name;
	    }
  }

private:
  int birth_year;
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {

	 Person person("Polina", "Sergeeva", 1960);
	  for (int year : {1959, 1960}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeFirstName(1965, "Appolinaria");
	  person.ChangeLastName(1967, "Ivanova");
	  for (int year : {1965, 1967}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }


	return 0;
}
