#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull poly_hash(const string& s,const ull prime,const ull x){
    ull hash = 0;
    for (int i = 0; i < s.length(); ++i)
        hash = (hash * x + s[i]) % prime;
    return hash;
}

vector<ull> precompute_hashes(const string& T, size_t P_length, ull prime, ull x){
    vector<ull> H(T.length() - P_length + 1);
    string s = T.substr(T.size() - P_length, P_length);
    H[T.length()-P_length] = poly_hash(s,prime,x);
    ull y = 1;
    for(int i = 1; i <= P_length; ++i)
        y = (y * x) % prime;
    for(int i = T.length()-P_length - 1; i >= 0; --i)
        H[i] = (x * H[i + 1] + T[i] - y * T[i + P_length]) % prime;
    return H;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    ull x = 1;
    ull prime = 1000000007;
    vector<ull> H = precompute_hashes(t,s.length(),prime,x);
    ull pHash = poly_hash(s, prime, x);
    std::vector<int> ans;
    for(size_t i = 0; i<H.size();++i){
        if(pHash == H[i]){
            if(t.substr(i, s.size()) == s){ans.push_back(i);}
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
