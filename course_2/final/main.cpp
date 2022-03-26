#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "database.h"
//#include "test_db.h"

#include <iostream>
#include <stdexcept>

#include "test_runner.h"

using namespace std;

string ParseEvent(istream& is) {
	string tmp;
	getline(is, tmp);
	auto it = tmp.begin();
	while (*it == ' ') {
		tmp.erase(it);
	}
	return tmp;
}

void TestAll();

int main() {
//  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
//  for (auto i = 0; i < 5; i++) {
/*
	  string line;
	if (i == 0) line = "Add 2017-11-21 Tuesday";
	if (i == 1) line = "Add 2017-11-20 Monday";
	if (i == 2) line= ("Add 2017-11-21 Weekly meeting");
	if (i == 3) line = ("Del date > 2017-11-20");
	if (i == 4) line = ("Last 2017-11-30");
*/
	istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
/*
  tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
  tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
  tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
  tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
  tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
  tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
  tr.RunTest(TestsMyCustom, "Мои тесты");
  tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
*/
}
