#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector <int> result_in;
  vector <int> result_pre;
  vector <int> result_post;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order_traversal(int vertex_idx){
    if(left[vertex_idx] == -1 && right[vertex_idx] == -1){
      result_in.push_back(key[vertex_idx]);
      return;
    }
    if(left[vertex_idx]!=-1)
      in_order_traversal(left[vertex_idx]);
    result_in.push_back(key[vertex_idx]);
    if(right[vertex_idx]!=-1)
      in_order_traversal(right[vertex_idx]);
  }

  void pre_order_traversal(int vertex_idx){
    if(left[vertex_idx] == -1 && right[vertex_idx] == -1){
      result_pre.push_back(key[vertex_idx]);
      return;
    }
    result_pre.push_back(key[vertex_idx]);
    if(left[vertex_idx] != -1)
      pre_order_traversal(left[vertex_idx]);
    
    if(right[vertex_idx] != -1)
      pre_order_traversal(right[vertex_idx]);
  }

  void post_order_traversal(int vertex_idx){
    if(left[vertex_idx] == -1 && right[vertex_idx] == -1){
      result_post.push_back(key[vertex_idx]);
      return;
    }
    if(left[vertex_idx] != -1)
      post_order_traversal(left[vertex_idx]);
    
    if(right[vertex_idx] != -1)
      post_order_traversal(right[vertex_idx]);
    result_post.push_back(key[vertex_idx]);
  }

  vector <int> in_order() {
    in_order_traversal(0);
    return result_in;
  }

  vector <int> pre_order() {
    pre_order_traversal(0);
    return result_pre;
  }

  vector <int> post_order() {
    post_order_traversal(0);
    return result_post;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

