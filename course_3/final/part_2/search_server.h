#pragma once
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <future>
#include <mutex>
using namespace std;

class InvertedIndex {
public:
	struct Results {
		size_t count;
		size_t docid;
	};

	InvertedIndex() = default;
	explicit InvertedIndex(istream& document_input);
	const vector<InvertedIndex::Results>& Lookup(string_view word) const;

	const size_t GetDocsCount() const {
		  return docs.size();
	}

	const  deque<string>& GetDocs() const {
		return docs;
	}

private:
  map<string_view, vector<InvertedIndex::Results>> index; // map -> vector
  deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input)
	  : index(InvertedIndex(document_input))
  {
  }
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> threads;
};
