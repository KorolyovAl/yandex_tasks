#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
    int year, month, day;
  int GetYear() const {
	  return year;
  }
  int GetMonth() const {
	  return month;
  }
  int GetDay() const {
	  return day;
  }
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year < rhs.year) return true;
	if (lhs.year == rhs.year && lhs.month < rhs.month) return true;
	if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day) return true;
	return false;
}

void CheckNextSymbolDate (stringstream& stream, string& date_check) {
	if (stream.peek() == '-') {
		stream.ignore(1);
	}
	else {
		stringstream out;
		out << "Wrong date format: " << date_check;
		throw runtime_error(out.str());
	}
}

Date GetCorrectDateForm (string date_check) {
	Date tmp;
	stringstream ss;
	ss << date_check;
	ss >> tmp.year;
	CheckNextSymbolDate(ss, date_check);
	ss >> tmp.month;
	CheckNextSymbolDate(ss, date_check);
	ss >> tmp.day;

	if (ss.fail() || !ss.eof()) {
		stringstream out;
		out << "Wrong date format: " << date_check;
		throw runtime_error(out.str());
	}
	if (tmp.month < 1 || tmp.month > 12) {
		stringstream out;
		out << "Month value is invalid: " << tmp.month;
		throw runtime_error(out.str());
	}
	if (tmp.day < 1 || tmp.day > 31) {
		stringstream out;
		out << "Day value is invalid: " << tmp.day;
		throw runtime_error(out.str());
	}
	return tmp;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
	  int check = 0;
	  for (auto x : database[date]) {
		  if (event == x) check = 1;
	  }
	  if (check == 0) database[date].push_back(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
	  int point_del = 0;
	  for (auto x : database[date]) {
		  if (x == event) {
			  database[date].erase(database[date].begin() + point_del);
			  return true;
		  }
		  point_del++;
	  }
	  return false;
  }

  int  DeleteDate(const Date& date) {
	  if (database[date].empty()) {
		  return 0;
	  }
	  else {
	  unsigned N = database[date].size();
	  database[date].clear();
	  return N;
	  }
  }

  void Find(const Date& date) const {
	  vector <string> event_tmp = database.at(date);
	  sort(event_tmp.begin(), event_tmp.end());
	  for (unsigned i = 0; i < event_tmp.size(); i++) {
		  cout << event_tmp[i] << endl;
	  }
  }

  void Print() const {

	  for (auto x : database) {
		  vector <string> event_tmp = x.second;
		  sort(event_tmp.begin(), event_tmp.end());
		  for (unsigned i = 0; i < event_tmp.size(); i++) {
			  cout << setw(4) << setfill('0') << x.first.year << "-"
					  << setw(2) << setfill('0') << x.first.month << "-"
					  << setw(2) << setfill('0') << x.first.day<< " "
					  << event_tmp[i] << endl;
		  }
	  }
  }

  bool CheckCommand (const string command) {
	  inner_command.clear();
  	for (auto x : command) {
  		if (x != ' ') inner_command += x;
  		else {
  			break;
  		}
  	}
  	return (inner_command == "Add" || inner_command == "Del" || inner_command == "Find" || inner_command == "Print");
  }

  void ExecuteCommands (const string command) {
	  // transcript of input
	  string word;
	  string date_str, event_str;
      int count = 0;
//      cout << command << endl;
	  for (unsigned x = 0; x < command.length(); x++) {
	 	if (command[x] == ' ' || x == command.length() - 1) {
	 		if ( x == command.length() - 1) {
	 			word += command[x];
	 		}
	 		if (count == 0) {
	 			word.clear();
	 		}
	 		if (count == 1) {
	 			date_str = word;
	 			word.clear();
	 		}
	 		if (count == 2) {
	 			event_str = word;
	 			word.clear();
	 		}
	 		count++;
	 	}
	 	else {
	 		word += command[x];
	 	}
	  }

	  // execute command
	  if (inner_command == "Add") {
		  time_point = GetCorrectDateForm(date_str);
		  AddEvent(time_point, event_str);
	  }
	  if (inner_command == "Del") {
		  time_point = GetCorrectDateForm(date_str);
		  if (event_str.empty()) {
			  int N =  DeleteDate(time_point);
			  cout << "Deleted " << N << " events" << endl;
		  } else {
			  if (DeleteEvent(time_point, event_str)) {
				  cout << "Deleted successfully" << endl;
			  }
			  else {
				  cout << "Event not found" << endl;
			  }
		  }
	  }
	  if (inner_command == "Find") {
		  time_point = GetCorrectDateForm(date_str);
		  if (!database[time_point].empty() && event_str.empty())
		  	  Find(time_point);
	  }
	  if (inner_command == "Print") {
		  Print();
	  }
  }

private:
  string busines;
  Date time_point;
  map <Date, vector<string>> database;
  string inner_command;
};

int main() {
  Database db;
  string command = "Add 0-1)-2 event1";
//  cout << command << endl;
//  string command;

  try {
  while (getline(cin, command)) {
	  if (db.CheckCommand(command) == true) {
		  db.ExecuteCommands(command);
	  }
	  else if (command.empty()) {
	  }
	  else {
		  cout << "Unknown command: " << command << endl;
	  }
  }
  }  catch (exception& ex) {
	  cout << ex.what() << endl;
  }

  return 0;
}
