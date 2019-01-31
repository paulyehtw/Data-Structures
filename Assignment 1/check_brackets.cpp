#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
            type(type),
            position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    string text;
    getline(cin, text);
    stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        Bracket next_brack = Bracket(next, position);
        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(next_brack);
        }
        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()) {
                cout << position + 1;
                return 0;
            }
            Bracket top_stack = opening_brackets_stack.top();
            if(top_stack.Matchc(next)) {
                opening_brackets_stack.pop();
            }
            else {
                cout << position+1;
                return 0;
            }

        }
    }
    if(opening_brackets_stack.empty()) {
        cout << "Success";
    }
    else {
        cout << (opening_brackets_stack.top()).position + 1;
    }
    return 0;
}