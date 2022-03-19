#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  // перебираем всю историю в хронологическом пор€дке
  for (const auto& item : names_by_year) {
    // если очередное им€ не относитс€ к будущему и отличаетс€ от предыдущего,
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      // добавл€ем его в историю
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  // нет истории Ч им€ неизвестно
  if (names.empty()) {
    return "";
  }
  // мен€ем пр€мой хронологический пор€док на обратный
  reverse(begin(names), end(names));

  // начинаем строить полное им€ с самого последнего
  string joined_name = names[0];

  // перебираем все последующие имена
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      // если это первое Ђисторическоеї им€, отдел€ем его от последнего скобкой
      joined_name += " (";
    } else {
      // если это не первое им€, отдел€ем от предыдущего зап€той
      joined_name += ", ";
    }
    // и добавл€ем очередное им€
    joined_name += names[i];
  }

  // если в истории было больше одного имени, мы открывали скобку Ч закроем еЄ
  if (names.size() > 1) {
    joined_name += ")";
  }
  // им€ со всей историей готово
  return joined_name;
}

// см. решение предыдущей задачи
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
    // найдЄм историю изменений имени и фамилии
    // в данном случае это излишне, так как нам достаточно узнать последние им€ и фамилию, но почему бы не использовать готовые функции?
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    // подготовим данные дл€ функции BuildFullName: возьмЄм последние им€ и фамилию или оставим их пустыми, если они неизвестны
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
    // получим полное им€ со всей историей
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    // получим полную фамилию со всей историей
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    // объединим их с помощью готовой функции
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

