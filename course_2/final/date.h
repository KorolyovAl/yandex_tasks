#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day);
  Date(vector<int> date);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  string GetString() const;

private:
  int year;
  int month;
  int day;
};

Date ParseDate(istream& ss);

ostream& operator<<(ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
