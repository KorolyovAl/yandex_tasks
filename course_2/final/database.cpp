#include "database.h"
#include "date.h"

using namespace std;

	void Database :: Add(const Date& date, const string& event) {
		if (storage[date].empty()) {
			storage[date].push_back(event);
			storage_check[date].insert(event);
		}
		else {
			if (storage_check[date].find(event) == storage_check[date].end()) {
				storage[date].push_back(event);
				storage_check[date].insert(event);
			}
		}
	}

	void Database :: Print(ostream& os) const{
	    for (const auto& item : storage) {
	      for (const string& event : item.second) {
	        os << item.first << " " << event << endl;
	      }
	    }
	}


	string Database :: Last(const Date& date) const {
		if (storage.empty()) {
			throw invalid_argument("");
		}
		auto it_map = storage.begin();
		if (date < it_map->first) {
			throw invalid_argument("");
		}
		it_map = storage.upper_bound(date);

		if (it_map != storage.begin()) {
			it_map--;
		}

		string out;
		out += it_map->first.GetString();
		out += " " + it_map->second.back();

		return out;
	}





