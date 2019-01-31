#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>


using namespace std;

class StackWithMax {
    vector<int> stack;
    vector<int> aux_stack;

public:
    void Push(int value) {
        stack.push_back(value);
        if(aux_stack.empty()){aux_stack.push_back(value);}
        if(value >= aux_stack.back()){aux_stack.push_back(value);}
    }

    void Pop() {
        assert(stack.size());
        if(stack.back() == aux_stack.back()){aux_stack.pop_back();}
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return aux_stack.back();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}