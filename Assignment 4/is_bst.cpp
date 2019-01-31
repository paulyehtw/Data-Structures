#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool is_bst = true;
vector<int> result_in;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(const vector<Node>& tree, int vertex_idx){
  if(tree[vertex_idx].left == -1 && tree[vertex_idx].right == -1){
    result_in.push_back(tree[vertex_idx].key);
    return;
  }
  if(tree[vertex_idx].left != -1)
    in_order_traversal(tree, tree[vertex_idx].left);
  result_in.push_back(tree[vertex_idx].key);
  if(tree[vertex_idx].right != -1)
    in_order_traversal(tree, tree[vertex_idx].right);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() > 0){
    in_order_traversal(tree, 0);
    for(size_t i = 0 ; i < result_in.size()-1 ; ++i){
      if(result_in[i] >= result_in[i+1]){
        is_bst = false;
        break;
      }
    }
  }
  return is_bst;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
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
