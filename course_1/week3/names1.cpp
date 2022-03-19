#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	  F_name[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  L_name[year] = last_name;
  }
  string GetFullName(int year) {
	  if ((F_name.empty() && L_name.empty()) ||	//оба контейнера пусты
		 (F_name.empty() && L_name.begin()->first > year) ||	// контейнер имени пуст, первое изменение фамилии было позже
		 (L_name.empty() && F_name.begin()->first > year)) {	// контейнер фамилии пуст, первое изменение имени было позже
		  return "Incognito";
	  }
	  if ( F_name.begin()->first > year && L_name.begin()->first > year) { // первое изменение имени и фамилии было позже
		  return "Incognito";
	  }

	  if (L_name.begin()->first > year || L_name.empty()) {
		  SearchFirstName(year);
		  string out = FirstName + " with unknown last name";
		  return out;
	  }
	  if (F_name.begin()->first > year || F_name.empty()) {
		  SearchLastName(year);
		  string out = LastName + " with unknown first name";
		  return out;
	  }
	  if (L_name[year].empty() && !F_name[year].empty()) {
		  SearchLastName(year);
		  string out = F_name[year] + " " + LastName;
		  return out;
	  }
	  if (F_name[year].empty() && !L_name[year].empty()) {
		  SearchFirstName(year);
		  string out = FirstName + " " + L_name[year];
		  return out;
	  }

	  if (F_name[year].empty() && L_name[year].empty() ) {

		  SearchFirstName(year);
		  SearchLastName(year);
		  string out = FirstName + " " + LastName;
		  return out;
	  }

	  string out = F_name[year] + " " + L_name[year];
	  return out;

  }
private:
  map <int, string> F_name;
  map <int, string> L_name;
  string FirstName;
  string LastName;
  int year;
  string SearchLastName (int year) {
	  int i = 0, r = 1;
	  if (year > L_name.begin()->first) {
	  	r = 1;
	  }
	  else r = -1;
	  while (L_name[year - i*r].empty() ){
	  	i++;
	  }
	  LastName = L_name[year - i*r];
	  return LastName;
  }
  string SearchFirstName (int year) {
	  int i = 0, r = 1;
	  if (year > F_name.begin()->first) {
	  	r = 1;
	  }
	  else r = -1;
	  while (F_name[year - i*r].empty() ){
	  	i++;
	  }
	  FirstName = F_name[year - i*r];
	  return FirstName;
  }
};

int main() {
	  Person person;

	  person.ChangeLastName(3, "3_2nd");
	  person.ChangeLastName(6, "6_2nd");

	  for (int year : {3, 4, 5, 6}) {
	  	cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeFirstName(-1, "-1_1st");
	  person.ChangeFirstName(2, "2_1st");

	  for (int year : {-1, 0, 1, 2, 3, 6}) {
	  	cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeFirstName(-2, "-2_1st");
	  person.ChangeLastName(7, "7_2nd");

	  for (int year : {-3, -2, -1, 0, 1, 2, 3, 6, 7, 8}) {
	  	cout << person.GetFullName(year) << endl;
	  }

	return 0;
}
