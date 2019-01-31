#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    void WriteResponse() const {
      cout << swaps_.size() << "\n";
      for (int i = 0; i < swaps_.size(); ++i) {
        cout << swaps_[i].first << " " << swaps_[i].second << "\n";
      }
    }

    void ReadData() {
      int n;
      cin >> n;
      data_.resize(n);
      for(int i = 0; i < n; ++i)
        cin >> data_[i];
    }

    void SiftDown(int i, int size){
      int min_idx = i;
      int l_idx = 2*i + 1;
      int r_idx = 2*i + 2;
      if(l_idx > (size-1) && r_idx > (size-1)){return;}
      if(l_idx <= (size-1) && data_[l_idx] < data_[min_idx]){
        min_idx = l_idx;
      }
      if(r_idx <= (size-1) && data_[r_idx] < data_[min_idx]){
        min_idx = r_idx;
      }
      if(i != min_idx){
        swap(data_[i], data_[min_idx]);
        swaps_.push_back(make_pair(i, min_idx));
        SiftDown(min_idx, size);
      }

    }

    void GenerateSwaps() {
      swaps_.clear();
      int size = data_.size();
      for(int i = size/2 - 1; i >= 0; --i){
        SiftDown(i, size);
      }

    }

public:
    void Solve() {
      ReadData();
      GenerateSwaps();
      WriteResponse();
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
