#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <ostream>
#include <algorithm>
#include <set>
#include "date.h"

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& os) const;

	template <class predicat_type>
	int RemoveIf(predicat_type predicate) {
		int count = 0;
		vector<Date> EmptyDates;
		for (auto it_map = storage.begin(); it_map != storage.end(); it_map++) {
			Date date = it_map->first;
			auto it_div = stable_partition(it_map->second.begin(), it_map->second.end(), [&predicate, date] (string& event)
					{return !predicate(date, event);});
			auto it_erase = it_map->second.end();
			for (;it_erase != it_div; it_erase--) {
				it_map->second.pop_back();
				if (it_map->second.size() == 0) {
					EmptyDates.push_back(date);
				}
			count++;
			}
			storage_check[date].clear();
			if (it_map->second.size() != 0) {
				storage_check[date].insert(it_map->second.begin(), it_div);
			}
		}

		for (auto& x : EmptyDates) {
			storage.erase(x);
			storage_check.erase(x);
		}
		EmptyDates.clear();
		return count;
	}

	template <class predicat_type>
	vector<string> FindIf (predicat_type predicate) const{
		vector<string> out;

		for (auto& x : storage) {
			Date date = x.first;
			for (auto& st : x.second) {
				string event = st;
				if (predicate(date, event)) {
					string tmp;
					tmp = date.GetString() + ' ' + event;
					out.push_back(tmp);
				}
			}
		}
		return out;
	}

	string Last(const Date& date) const;

private:
	map<Date, vector<string>> storage;
	map<Date, set<string>> storage_check;
};
