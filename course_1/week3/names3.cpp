#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  // ���������� ��� ������� � ��������������� �������
  for (const auto& item : names_by_year) {
    // ���� ��������� ��� �� ��������� � �������� � ���������� �� �����������,
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      // ��������� ��� � �������
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  // ��� ������� � ��� ����������
  if (names.empty()) {
    return "";
  }
  // ������ ������ ��������������� ������� �� ��������
  reverse(begin(names), end(names));

  // �������� ������� ������ ��� � ������ ����������
  string joined_name = names[0];

  // ���������� ��� ����������� �����
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      // ���� ��� ������ ������������� ���, �������� ��� �� ���������� �������
      joined_name += " (";
    } else {
      // ���� ��� �� ������ ���, �������� �� ����������� �������
      joined_name += ", ";
    }
    // � ��������� ��������� ���
    joined_name += names[i];
  }

  // ���� � ������� ���� ������ ������ �����, �� ��������� ������ � ������� �
  if (names.size() > 1) {
    joined_name += ")";
  }
  // ��� �� ���� �������� ������
  return joined_name;
}

// ��. ������� ���������� ������
string BuildFullName(const string& first_name, const string& last_name) {
  if (first_name.empty() && last_name.empty()) {
    return "No person";
  } else if (first_name.empty()) {
    return last_name;
  } else if (last_name.empty()) {
    return first_name;
  } else {
    return first_name + " " + last_name;
  }
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

  string GetFullName(int year) {
    // ����� ������� ��������� ����� � �������
    // � ������ ������ ��� �������, ��� ��� ��� ���������� ������ ��������� ��� � �������, �� ������ �� �� ������������ ������� �������?
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    // ���������� ������ ��� ������� BuildFullName: ������ ��������� ��� � ������� ��� ������� �� �������, ���� ��� ����������
    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) {
    // ������� ������ ��� �� ���� ��������
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    // ������� ������ ������� �� ���� ��������
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    // ��������� �� � ������� ������� �������
    return BuildFullName(first_name, last_name);
  }

private:
  vector<string> FindFirstNamesHistory(int year) {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) {
    return FindNamesHistory(last_names, year);
  }
  int birth_year;
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {
	   Person person("", "Sergeeva", 1960);
	   person.ChangeFirstName(1961, "Appolinaria");
	  person.ChangeFirstName(1965, "Polina");
	  person.ChangeFirstName(1965, "Appolinaria");

	  person.ChangeLastName(1965, "Sergeeva");
	  person.ChangeLastName(1965, "Volkova");
	  person.ChangeLastName(1965, "Volkova-Sergeeva");

	  for (int year : {1960,1964, 1965, 1966}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	return 0;
}
