#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include<array>
#include <numeric>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

void UpdateDocumentBaseSingleThread(istream& document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index(document_input);
    swap(index.GetAccess().ref_to_value, new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  threads.push_back(async(UpdateDocumentBaseSingleThread, ref(document_input), ref(index)));
}

void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index_out) {

    Synchronized<InvertedIndex>::Access ac = index_out.GetAccess();
    size_t doc_size = ac.ref_to_value.GetDocs().size();

    vector<size_t> docid_count(doc_size);
    vector<int64_t> docids(doc_size);

    for (string current_query; getline(query_input, current_query); ) {
        docid_count.assign(docid_count.size(), 0);
        InvertedIndex& index = ac.ref_to_value;
        for (string_view word : SplitIntoWordsView(current_query)) {
            for (const auto& result : index.Lookup(word)) {
                docid_count[result.docid] += result.count;
            }
        }

        iota(docids.begin(), docids.end(), 0);
        partial_sort(
            docids.begin(),
            Head(docids, 5).end(),
            docids.end(),
            [&docid_count](int64_t lhs, int64_t rhs) {
                return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
            }
        );

        search_results_output << current_query << ':';
        for (size_t docid : Head(docids, 5)) {
            const size_t hitcount = docid_count[docid];
            if (hitcount == 0) break;

            search_results_output << " {"
                << "docid: " << docid << ", "
                << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    threads.push_back(async(AddQueriesStreamSingleThread, ref(query_input), ref(search_results_output), ref(index)));
}

const vector<InvertedIndex::Results>& InvertedIndex::Lookup(string_view word) const
{
    static vector<InvertedIndex::Results> tmp;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    }
    else {
        return tmp;
    }
}

InvertedIndex::InvertedIndex(istream& document_input) {
    for (string document; getline(document_input, document); ) {
        docs.push_back(move(document));

        size_t docid = docs.size() - 1;
        for (string_view word : SplitIntoWordsView(docs.back())) {
            auto& word_docs = index[word];
            if (word_docs.empty() || word_docs.back().docid != docid) {
                word_docs.push_back({ 1, docid });
            }
            else {
                word_docs.back().count++;
            }
        }
    }
}
