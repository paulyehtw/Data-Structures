#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
bool is_bst = true;
vector<long long> result;

struct Node {
  long long key;
  long long left;
  long long right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, long long left_, long long right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(const vector<Node>& tree, long long vertex_idx){
  if(!is_bst){return;}
  if(tree[vertex_idx].left != -1 && tree[tree[vertex_idx].left].key != tree[vertex_idx].key)
		in_order_traversal(tree, tree[vertex_idx].left);
  else if (tree[vertex_idx].left != -1 && tree[tree[vertex_idx].left].key == tree[vertex_idx].key)
		is_bst = false;
  result.push_back(tree[vertex_idx].key);
  if(tree[vertex_idx].right != -1)
		in_order_traversal(tree, tree[vertex_idx].right);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() > 0){
    in_order_traversal(tree, 0);
    if(!is_bst)
      return false;
    for(size_t i = 0 ; i < result.size()-1 ; ++i){
      if(result[i] > result[i+1])
        return false;
    }
  }
  return true;
}

int main() {
  long long nodes;
  cin >> nodes;
  vector<Node> tree;
  for (long long i = 0; i < nodes; ++i) {
    long long key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
