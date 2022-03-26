#include "date.h"
#include <iomanip>
#include <sstream>

  Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

  Date::Date(vector<int> date) {
	  year = date[0];
	  if (date[1] > 12 || date[1] < 1) {
	        throw logic_error("Month value is invalid: " + to_string(date[1]));
	      }
	  month = date[1];
	  if (date[2] > 31 || date[2] < 1) {
	        throw logic_error("Day value is invalid: " + to_string(date[2]));
	      }
	  day = date[2];
  }

  int Date::GetYear() const {
    return year;
  }
  int Date::GetMonth() const {
    return month;
  }
  int Date::GetDay() const {
    return day;
  }

  string Date::GetString() const {
	  stringstream ss;
	  ss << setfill('0');
	  ss << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day;
	  string out;
	  char symb;
	  while (ss >> symb) {
		  out += symb;
	  }
	  return out;
  }

Date ParseDate(istream& ss) {
	int year, month, day;
	ss >> year;
	ss.ignore(1);

	ss >> month;
	ss.ignore(1);

	ss >> day;

	return {year, month, day};

}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
					return true;
				}
				else if (lhs.GetYear() == rhs.GetYear()) {

					if (lhs.GetMonth() < rhs.GetMonth()) {
						return true;
					}
					else if (lhs.GetMonth() == rhs.GetMonth()) {

						if (lhs.GetDay() < rhs.GetDay()) {
							return true;
						}
						else if (lhs.GetDay() == rhs.GetDay()) {
							return false;
						}
						else return false;
					}
					else return false;
				}
				else return false;
}


