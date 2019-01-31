#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};


class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<Query>> elements;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
        elements.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {

        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elements[query.ind].size()) - 1; i >= 0; --i)
                cout << elements[query.ind][i].s << " ";
            cout << "\n";
        }
        else {

            size_t T = hash_func(query.s);
            if (query.type == "find"){
                bool found = false;
                for (int i = 0; i < elements[T].size(); i++){
                    if (elements[T][i].s == query.s){
                        found = true;
                        break;
                    }
                }
                writeSearchResult(found);
            }
            else if (query.type == "add"){
                bool added = false;
                for (int i = 0; i < elements[T].size(); i++){
                    if (elements[T][i].s == query.s){
                        added = true;
                        break;
                    }
                }
                if (!added){elements[T].push_back(query);}
            }
            else if (query.type == "del"){
                for (int i = 0; i < elements[T].size(); i++){
                    if (elements[T][i].s == query.s){
                        elements[T].erase(elements[T].begin()+i);
                        break;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    system("pause");
    return 0;
}