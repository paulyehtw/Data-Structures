#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  int root_idx;
  std::cin >> n;
  Node node;
  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0) {
      nodes[child_index].setParent(&nodes[parent_index]);
    }
    else {
      root_idx = child_index;
    }
    nodes[child_index].key = child_index;
  }
  int maxHeight = 1;
  queue<Node*> Q;
  Node *root = &nodes[root_idx];
  Q.push(root);
  int L1 = 1;
  int L2 = 0;
  while(Q.size() > 0){
    Node *parent = Q.front();
    L2 += Q.front()->children.size();
    Q.pop();
    L1--;
    if(L1 == 0 && L2 > 0){
      L1 = L2;
      L2 = 0;
      ++maxHeight;
    }
    if(parent->children.size() > 0){
      for(int c = 0; c < parent->children.size(); ++c){
        Q.push(parent->children[c]);
      }
    }
  }
  std::cout << maxHeight << std::endl;
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
