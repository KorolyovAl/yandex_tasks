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
  istringstream words_input(line); // string_view ьс
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  index =InvertedIndex(document_input);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    vector<size_t> docid_count(index.GetDocsCount());
    vector<int64_t> docids(index.GetDocsCount());

    for (string current_query; getline(query_input, current_query); ) {
        docid_count.assign(docid_count.size(), 0);
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

void SearchServer::AddQueriesStream_1(
    istream& query_input, ostream& search_results_output
) {
    vector<pair<size_t, size_t>> docid_count(index.GetDocsCount()); // vector<pair<size_t, size_t>> docid_count -> first = docid; second = hitcount
    vector<int64_t> docids(index.GetDocsCount());

    for (string current_query; getline(query_input, current_query); ) {

        docid_count.assign(docid_count.size(), { 0, 0 });

        for (string_view word : SplitIntoWordsView(current_query)) {
            for (const auto& docid : index.Lookup(static_cast<std::string>(word))) {
                //docid_count[docid].first = docid;
                //docid_count[docid].second++;
            }
        }

        iota(docids.begin(), docids.end(), 0);

        vector<pair<size_t, size_t>> search_results(
            docid_count.begin(), docid_count.end()
        );

        if (search_results.size() <= 5) {
            partial_sort(   // partial_sort
                begin(search_results),
                begin(search_results) + search_results.size() - 1,
                end(search_results),
                [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                    int64_t lhs_docid = lhs.first;
                    auto lhs_hit_count = lhs.second;
                    int64_t rhs_docid = rhs.first;
                    auto rhs_hit_count = rhs.second;
                    return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                }
            );
        }
        else {
            partial_sort(   // partial_sort
                begin(search_results),
                begin(search_results) + 5,
                end(search_results),
                [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                    int64_t lhs_docid = lhs.first;
                    auto lhs_hit_count = lhs.second;
                    int64_t rhs_docid = rhs.first;
                    auto rhs_hit_count = rhs.second;
                    return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                }
            );
        }

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            if (hitcount != 0) {
                search_results_output << " {"
                    << "docid: " << docid << ", "
                    << "hitcount: " << hitcount << '}';
            }
        }
        search_results_output << endl;
    }
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
